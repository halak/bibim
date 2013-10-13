using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml.Linq;
using Bibim.Animation;
using Bibim.Graphics;
using Ionic.Zip;
using Rectangle = Microsoft.Xna.Framework.Rectangle;
using Image = Bibim.Graphics.Image;
using GDIRectangle = System.Drawing.Rectangle;
using GDIGraphics = System.Drawing.Graphics;
using GDIImage = System.Drawing.Image;
using Dict = System.Collections.Generic.Dictionary<object, object>;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class ImportTimelineFX : CookingNode<SparkSet>
    {
        #region Keyframe (Nested Struct)
        private struct Keyframe
        {
            public float Time;
            public float Value;

            public Keyframe(float time, float value)
            {
                Time = time;
                Value = value;
            }
        }
        #endregion

        #region Graph (Nested class)
        private class Graph : List<Keyframe>
        {
            #region Properties
            public new Keyframe this[int index]
            {
                get { return base[index]; }
                set { base[index] = value; }
            }

            public float this[float time]
            {
                get
                {
                    if (Count == 0)
                        return 0.0f;
                    if (time <= this[0].Time)
                        return this[0].Value;
                    if (time >= this[Count - 1].Time)
                        return this[Count - 1].Value;

                    float priorTime = this[0].Time;
                    for (int i = 1; i < Count; i++)
                    {
                        float nextTime = this[i].Time;
                        if (priorTime <= time && time < nextTime)
                        {
                            float t = (time - priorTime) / (nextTime - priorTime);
                            return MathExtension.Lerp(this[i - 1].Value, this[i].Value, t);
                        }

                        priorTime = nextTime;
                    }

                    return 0.0f;
                }
            }
            #endregion

            #region Constructors
            public Graph()
            {
            }

            public Graph(int capacity)
                : base(capacity)
            {
            }

            public Graph(IEnumerable<Keyframe> collection)
                : base(collection)
            {
            }
            #endregion

            #region Methods
            public void Transform(Func<float, float> f)
            {
                if (f == null)
                    return;

                for (int i = 0; i < Count; i++)
                    this[i] = new Keyframe(this[i].Time, f(this[i].Value));
            }

            public static Graph Merge(Graph left, Graph right, Func<float, float, float> merge)
            {
                if (IsEmpty(left) && IsEmpty(right))
                    return new Graph();
                else if (IsEmpty(left))
                    return new Graph(right);
                else if (IsEmpty(right))
                    return new Graph(left);

                var result = new Graph(left.Count + right.Count);

                var leftIndex = 0;
                var rightIndex = 0;
                while (leftIndex < left.Count && rightIndex < right.Count)
                {
                    var leftTime = leftIndex < left.Count ? left[leftIndex].Time : float.PositiveInfinity;
                    var rightTime = rightIndex < right.Count ? right[rightIndex].Time : float.PositiveInfinity;

                    if (AlmostEquals(leftTime, rightTime))
                    {
                        var value = merge(left[leftIndex].Value, right[rightIndex].Value);
                        result.Add(new Keyframe(leftTime, value));
                        leftIndex++;
                        rightIndex++;
                    }
                    else if (leftTime < rightTime)
                    {
                        var value = merge(left[leftIndex].Value, right[leftTime]);
                        result.Add(new Keyframe(leftTime, value));
                        leftIndex++;
                    }
                    else // if (leftTime > rightTime)
                    {
                        var value = merge(left[rightTime], right[rightIndex].Value);
                        result.Add(new Keyframe(rightTime, value));
                        rightIndex++;
                    }
                }

                return result;
            }

            private static bool IsEmpty(Graph value)
            {
                return value == null || value.Count == 0;
            }
            #endregion
        }
        #endregion

        #region Properties
        public string Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public ImportTimelineFX()
            : this(null)
        {
        }

        public ImportTimelineFX(string input)
        {
            Input = input;
        }
        #endregion

        #region Methods
        public override SparkSet Cook(CookingContext context)
        {
            string assetPath = Path.Combine(context.Directory, context.ExpandVariables(Input));
            string input = Path.Combine(context.BaseDirectory, assetPath);
            if (File.Exists(input) == false)
                throw new FileNotFoundException(string.Empty, input);

            context.AddDependency(input);

            using (var zip = new ZipFile(input))
            {
                XDocument data = null;
                var images = new Dictionary<string, Bitmap>();

                foreach (var item in zip.Entries)
                {
                    if (item.IsDirectory)
                        continue;

                    var extension = Path.GetExtension(item.FileName);
                    if (string.Compare(extension, ".png", true) == 0 ||
                        string.Compare(extension, ".jpg", true) == 0 ||
                        string.Compare(extension, ".jpeg", true) == 0 ||
                        string.Compare(extension, ".bmp", true) == 0 ||
                        string.Compare(extension, ".tpa", true) == 0)
                    {
                        using (var stream = item.OpenReader())
                            images.Add(item.FileName, new Bitmap(stream));
                    }
                    else if (string.Compare(item.FileName, "Data.xml", true) == 0)
                    {
                        Trace.Assert(data == null);

                        using (var stream = item.OpenReader())
                            data = XDocument.Load(stream);
                    }
                }

                return Import(data, images);
            }
        }

        private enum EffectType
        {
            Point,
            Area,
            Line,
            Ring,
        }

        private enum EmissionType
        {
            Grid,
            Inwards,
            Outwards,
            InOutwards,
            Specified,
        }

        private enum AngleType
        {
            Align,
            Random,
            Specify,
        }

        private enum ImportOption
        {
            UNKNOWN,
            FULLCOLOUR
        }

        private static SparkSet Import(XDocument doc, Dictionary<string, Bitmap> imageFiles)
        {
            Trace.Assert(doc.Root.Name == "EFFECTS");

            var sparks = new SparkSet();

            ReadImages(sparks, doc, imageFiles);
            ReadEffects(sparks, doc);

            return sparks;
        }

        private static void ReadImages(SparkSet sparks, XDocument doc, Dictionary<string, Bitmap> imageFiles)
        {
            foreach (var item in doc.Root.Element("SHAPES").Elements("IMAGE"))
            {
                var url = (string)item.Attribute("URL");
                var filename = Path.GetFileName(url);
                var width = (int)item.Attribute("WIDTH");
                var height = (int)item.Attribute("HEIGHT");
                var frames = (int)item.Attribute("FRAMES");
                var index = (int)item.Attribute("INDEX");
                ImportOption importOption;
                if (Enum.TryParse((string)item.Attribute("IMPORT_OPTION"), out importOption) == false)
                    importOption = ImportOption.UNKNOWN;
                var maxRadius = (double)item.Attribute("MAX_RADIUS");

                if (string.IsNullOrEmpty(filename) ||
                    width <= 0 ||
                    height <= 0 ||
                    frames <= 0 ||
                    index < 0 ||
                    importOption == ImportOption.UNKNOWN ||
                    maxRadius < 0.0f)
                    continue;

                var bitmap = imageFiles[filename];

                if (frames == 1)
                {
                    sparks.Images.Images.Add(string.Format("{0}-0", index), new Image(string.Empty, Rectangle.Empty)
                    {
                        Tag = new ImageCookingTag(bitmap)
                    });
                }
                else
                {
                    int framePerRow = bitmap.Width / width;
                    for (int i = 0; i < frames; i++)
                    {
                        var bitmapPart = new Bitmap(width, height);

                        int x = (i % framePerRow) * width;
                        int y = (i / framePerRow) * height;
                        using (var g = GDIGraphics.FromImage(bitmapPart))
                            g.DrawImage(bitmap, 0, 0, new GDIRectangle(x, y, width, height), GraphicsUnit.Pixel);

                        sparks.Images.Images.Add(string.Format("{0}-{1}", index, i), new Image(string.Empty, Rectangle.Empty)
                        {
                            Tag = new ImageCookingTag(bitmapPart)
                        });
                    }
                }
            }
        }

        private static void ReadEffects(SparkSet sparks, XDocument doc)
        {
            var usedImages = new List<string>();

            foreach (var effectElement in doc.Descendants("EFFECT"))
            {
                var spark = new Dict();

                var effect = new
                {
                    Name = GetEffectFullName(effectElement),
                    Type = (EffectType)(int)effectElement.Attribute("TYPE"),
                    GridX = (int)effectElement.Attribute("MAXGX"),
                    GridY = (int)effectElement.Attribute("MAXGY"),
                    EmissionType = (EmissionType)(int)effectElement.Attribute("EMISSION_TYPE"), //----------//
                    RingArc = (float)effectElement.Attribute("ELLIPSE_ARC"), //----------//
                    Length = (int)effectElement.Attribute("EFFECT_LENGTH"),
                    IsUniform = (bool)effectElement.Attribute("UNIFORM"), //----------//
                    // IsHandleCenter = (bool)effectElement.Attribute("HANDLE_CENTER"), //----------//
                    // HandleX = effectElement.Attribute("HANDLE_X"), //----------//
                    // HandleY = effectElement.Attribute("HANDLE_Y"), //----------//
                    IsTraverseEdge = (bool)effectElement.Attribute("TRAVERSE_EDGE"), //----------//
                    IsEndBehavior = (bool)effectElement.Attribute("END_BEHAVIOUR"), //----------//
                    IsDistanceSetByLife = (bool)effectElement.Attribute("DISTANCE_SET_BY_LIFE"), //----------//
                    IsReverseSpawnDirection = (bool)effectElement.Attribute("REVERSE_SPAWN_DIRECTION"), //----------//

                    GlobalAmount = ReadGraph(effectElement.Elements("AMOUNT")),
                    GlobalLife = ReadGraph(effectElement.Elements("LIFE")),
                    GlobalSizeX = ReadGraph(effectElement.Elements("SIZEX")),
                    GlobalSizeY = ReadGraph(effectElement.Elements("SIZEY")),
                    GlobalSpeed = ReadGraph(effectElement.Elements("VELOCITY")),
                    GlobalWeight = ReadGraph(effectElement.Elements("WEIGHT")),
                    GlobalSpin = ReadGraph(effectElement.Elements("SPIN")),
                    GlobalAlpha = ReadGraph(effectElement.Elements("ALPHA")),
                    GlobalStretch = ReadGraph(effectElement.Elements("STRETCH")), //----------//
                    EmissionRange = ReadGraph(effectElement.Elements("EMISSIONRANGE")),
                    EmissionAngle = ReadGraph(effectElement.Elements("EMISSIONANGLE")),
                    AreaWidth = ReadGraph(effectElement.Elements("AREA_WIDTH")),
                    AreaHeight = ReadGraph(effectElement.Elements("AREA_HEIGHT")),
                    EffectAngle = ReadGraph(effectElement.Elements("ANGLE")), //----------//
                };

                var groupIndex = 1;
                foreach (var emitterElement in effectElement.Elements("PARTICLE").OrderBy((e)=>(int)e.Attribute("LAYER")))
                {
                    var emitter = new
                    {
                        HandleX = (int)emitterElement.Attribute("HANDLE_X"),
                        HandleY = (int)emitterElement.Attribute("HANDLE_Y"),
                        // BlendMode = (int)emitterElement.Attribute("BLENDMODE"),
                        IsRelative = (bool)emitterElement.Attribute("RELATIVE"),
                        IsRandomColor = (bool)emitterElement.Attribute("RANDOM_COLOR"),
                        IsSingleParticle = (bool)emitterElement.Attribute("SINGLE_PARTICLE"), //----------//
                        // Layer = (int)emitterElement.Attribute("LAYER"),
                        // Name = (string)emitterElement.Attribute("NAME"),
                        IsAnimate = (bool)emitterElement.Attribute("ANIMATE"), //----------//
                        IsAnimateOnce = (bool)emitterElement.Attribute("ANIMATE_ONCE"), //----------//
                        Frame = (int)emitterElement.Attribute("FRAME"), //----------//
                        RandomStartFrame = (int)emitterElement.Attribute("RANDOM_START_FRAME"), //----------//
                        IsAnimateForwardDirection = (bool)emitterElement.Attribute("ANIMATION_DIRECTION"), //----------//
                        IsUniform = (bool)emitterElement.Attribute("UNIFORM"),
                        AngleType = (AngleType)(int)emitterElement.Attribute("ANGLE_TYPE"),
                        AngleOffset = (int)emitterElement.Attribute("ANGLE_OFFSET"),
                        IsLockAngle = (bool)emitterElement.Attribute("LOCK_ANGLE"),
                        IsAngleRelative = (bool)emitterElement.Attribute("ANGLE_RELATIVE"),
                        IsEffectEmissionUsed = (bool)emitterElement.Attribute("USE_EFFECT_EMISSION"),
                        ColorRepeat = (int)emitterElement.Attribute("COLOR_REPEAT"),
                        AlphaRepeat = (int)emitterElement.Attribute("ALPHA_REPEAT"),
                        IsOneShot = (bool)emitterElement.Attribute("ONE_SHOT"), //----------//
                        IsHandleCentered = (bool)emitterElement.Attribute("HANDLE_CENTERED"),
                        // IsGroupParticles = (bool)emitterElement.Attribute("GROUP_PARTICLES"),
                        ShapeIndex = int.Parse(emitterElement.Element("SHAPE_INDEX").Value),

                        Life = ReadGraph(emitterElement.Elements("LIFE")),
                        Amount = ReadGraph(emitterElement.Elements("AMOUNT")),
                        BaseSpeed = ReadGraph(emitterElement.Elements("BASE_SPEED")),
                        BaseWeight = ReadGraph(emitterElement.Elements("BASE_WEIGHT")),
                        BaseSizeX = ReadGraph(emitterElement.Elements("BASE_SIZE_X")),
                        BaseSizeY = ReadGraph(emitterElement.Elements("BASE_SIZE_Y")),
                        BaseSpin = ReadGraph(emitterElement.Elements("BASE_SPIN")),
                        LifeVariation = ReadGraph(emitterElement.Elements("LIFE_VARIATION")),
                        AmountVariation = ReadGraph(emitterElement.Elements("AMOUNT_VARIATION")),
                        SpeedVariation = ReadGraph(emitterElement.Elements("VELOCITY_VARIATION")),
                        WeightVariation = ReadGraph(emitterElement.Elements("WEIGHT_VARIATION")),
                        SizeXVariation = ReadGraph(emitterElement.Elements("SIZE_X_VARIATION")),
                        SizeYVariation = ReadGraph(emitterElement.Elements("SIZE_Y_VARIATION")),
                        SpinVariation = ReadGraph(emitterElement.Elements("SPIN_VARIATION")),
                        DirectionVariation = ReadGraph(emitterElement.Elements("DIRECTION_VARIATION")), //----------//
                        AlphaOvertime = ReadGraph(emitterElement.Elements("ALPHA_OVERTIME")),
                        SpeedOvertime = ReadGraph(emitterElement.Elements("VELOCITY_OVERTIME")),
                        WeightOvertime = ReadGraph(emitterElement.Elements("WEIGHT_OVERTIME")),
                        ScaleXOvertime = ReadGraph(emitterElement.Elements("SCALE_X_OVERTIME")),
                        ScaleYOvertime = ReadGraph(emitterElement.Elements("SCALE_Y_OVERTIME")),
                        SpinOvertime = ReadGraph(emitterElement.Elements("SPIN_OVERTIME")),
                        RedOvertime = ReadGraph(emitterElement.Elements("RED_OVERTIME")),
                        GreenOvertime = ReadGraph(emitterElement.Elements("GREEN_OVERTIME")),
                        BlueOvertime = ReadGraph(emitterElement.Elements("BLUE_OVERTIME")),
                        Direction = ReadGraph(emitterElement.Elements("DIRECTION")), //----------//
                        DirectionVariationOvertime = ReadGraph(emitterElement.Elements("DIRECTION_VARIATIONOT")), //----------//
                        // FrameRateOvertime = ReadGraph(emitterElement.Elements("FRAMERATE_OVERTIME")),
                        StretchOvertime = ReadGraph(emitterElement.Elements("STRETCH_OVERTIME")), //----------//
                        SpeedAdjuster = ReadGraph(emitterElement.Elements("GLOBAL_VELOCITY")), //----------//
                        EmissionRange = ReadGraph(effectElement.Elements("EMISSIONRANGE")),
                        EmissionAngle = ReadGraph(effectElement.Elements("EMISSIONANGLE")),
                    };

                    var groupEmitter = new Dict()
                    {
                        { "Flow", FloatToValue(emitter.Amount, null/*emitter.AmountVariation*/, null, effect.GlobalAmount) },
                        { "Force", FloatToValue(emitter.BaseSpeed, emitter.SpeedVariation, emitter.SpeedOvertime, effect.GlobalSpeed) },
                    };

                    switch (effect.Type)
                    {
                        case EffectType.Point:
                            groupEmitter["Zone"] = LuaArray(0, 0);
                            break;
                        case EffectType.Area:
                            {
                                if (GetSingleValueOrNull(effect.AreaWidth).HasValue == false ||
                                    GetSingleValueOrNull(effect.AreaHeight).HasValue == false)
                                    Trace.TraceWarning("Effect Area Width/Height의 그래프는 지원하지 않습니다.");

                                var width = GetFirstValue(effect.AreaWidth);
                                var height = GetFirstValue(effect.AreaHeight);
                                groupEmitter["Zone"] = LuaArray(-width / 2.0f, -height / 2.0f, width, height);
                            }
                            break;
                        case EffectType.Line:
                            {
                                if (GetSingleValueOrNull(effect.AreaWidth).HasValue == false)
                                    Trace.TraceWarning("Effect Area Width/Height의 그래프는 지원하지 않습니다.");

                                var length = GetFirstValue(effect.AreaWidth);
                                groupEmitter["Zone"] = LuaArray(-length / 2.0f, -1.0f, length, 2.0f);
                            }
                            break;
                        case EffectType.Ring:
                            {
                                if (GetSingleValueOrNull(effect.AreaWidth).HasValue == false ||
                                    GetSingleValueOrNull(effect.AreaHeight).HasValue == false)
                                    Trace.TraceWarning("Effect Area Width/Height의 그래프는 지원하지 않습니다.");

                                var width = GetFirstValue(effect.AreaWidth);
                                var height = GetFirstValue(effect.AreaHeight);
                                var radius = Math.Max(width, height);
                                groupEmitter["Zone"] = new Dict() { { 1, 0 }, { 2, 0 }, { "Radius", MinMax(radius - 1.0f, radius) } };
                            }
                            // effect.GridX;
                            // effect.GridY;
                            break;
                    }

                    {
                        var emissionAngle = (emitter.IsEffectEmissionUsed) ? effect.EmissionAngle : emitter.EmissionAngle;
                        var emissionRange = (emitter.IsEffectEmissionUsed) ? effect.EmissionRange : emitter.EmissionRange;
                        if (GetSingleValueOrNull(emissionAngle).HasValue == false ||
                            GetSingleValueOrNull(emissionRange).HasValue == false)
                            Trace.TraceWarning("Emission Angle/Range의 그래프는 지원하지 않습니다.");
                        double emissionAngleValue = MathExtension.DegreeToRadian((double)GetFirstValue(emissionAngle));
                        double emissionRangeValue = MathExtension.DegreeToRadian((double)GetFirstValue(emissionRange));
                        double directionX = +Math.Sin(emissionAngleValue);
                        double directionY = -Math.Cos(emissionAngleValue);
                        if (AlmostEquals(emissionRangeValue, 0.0))
                            groupEmitter["Direction"] = new Dict() { { 1, directionX }, { 2, directionY } };
                        else
                            groupEmitter["Direction"] = new Dict() { { 1, directionX }, { 2, directionY }, { "Angle", emissionRangeValue * 2 } };
                    }

                    var group = new Dict()
                    {
                        { "Lifetime", FloatGraphToValue(emitter.Life, emitter.LifeVariation, null, effect.GlobalLife, (x) => x / 1000.0f) },
                        { "Opacity", FloatGraphToValue(new Graph() { new Keyframe(0.0f, 1.0f) }, null, emitter.AlphaOvertime, effect.GlobalAlpha) },
                        { "AngularSpeed", FloatGraphToValue(emitter.BaseSpin, emitter.SpinVariation, emitter.SpinOvertime, effect.GlobalSpin) },
                        { "Stretch", FloatGraphToValue(new Graph() { new Keyframe(0.0f, 1.0f) }, null, emitter.StretchOvertime, effect.GlobalStretch) },
                        { "MotionRandomness", FloatGraphToValue(emitter.Direction, emitter.DirectionVariation, emitter.DirectionVariationOvertime, null) },
                        { "Emitter", groupEmitter },
                    };

                    var mass = FloatGraphToValue(emitter.BaseWeight, emitter.WeightVariation, emitter.WeightOvertime, effect.GlobalWeight, (x) => x / 1000.0f);
                    if (IsValidMass(mass))
                    {
                        group["Mass"] = mass;
                        group["Gravity"] = LuaArray(0.0f, 980.0f);
                    }

                    if (emitter.ColorRepeat > 0)
                        Trace.TraceWarning("Color 반복은 지원하지 않습니다.");
                    if (emitter.AlphaRepeat> 0)
                        Trace.TraceWarning("Alpha 반복은 지원하지 않습니다.");

                    if (emitter.IsRandomColor)
                    {
                        var randomColors = new Dict();
                        var index = 1;
                        for (float t = 0.0f; t <= 1.0f; t += 0.02f)
                        {
                            randomColors[index++] = LuaArray(emitter.RedOvertime[t] / 255.0f,
                                                             emitter.GreenOvertime[t] / 255.0f,
                                                             emitter.BlueOvertime[t] / 255.0f);
                        }
                        group["RandomColors"] = randomColors;
                    }
                    else
                    {
                        group["Red"] = ColorGraphToValue(emitter.RedOvertime);
                        group["Green"] = ColorGraphToValue(emitter.GreenOvertime);
                        group["Blue"] = ColorGraphToValue(emitter.BlueOvertime);
                    }

                    if (effect.IsUniform == false || emitter.IsUniform == false)
                        Trace.TraceWarning("가로/세로 크기가 분리된 그래프는 지원하지 않습니다.");

                    var image = sparks.Images.Find(string.Format("{0}-{1}", emitter.ShapeIndex, 0));
                    var imageWidth = ((ImageCookingTag)image.Tag).Bitmap.Width;
                    var imageHeight = ((ImageCookingTag)image.Tag).Bitmap.Height;
                    group["Size"] = FloatGraphToValue(emitter.BaseSizeX, emitter.SizeXVariation, emitter.ScaleXOvertime, effect.GlobalSizeX, (x) => x / (float)imageWidth);
                    
                    if (emitter.IsUniform == false)
                        group["SizeVertical"] = FloatGraphToValue(emitter.BaseSizeY, emitter.SizeYVariation, emitter.ScaleYOvertime, effect.GlobalSizeY, (x) => x / (float)imageHeight);

                    if ((emitter.IsHandleCentered == false) &&
                        (imageWidth / 2 != emitter.HandleX || imageHeight / 2 != emitter.HandleY))
                    {
                        group["RotationCenter"] = LuaArray((float)emitter.HandleY / (float)imageWidth,
                                                           (float)emitter.HandleY / (float)imageHeight);
                    }

                    int existsImageIndex = usedImages.IndexOf(string.Format("{0}-0", emitter.ShapeIndex));
                    if (existsImageIndex == -1)
                    {
                        existsImageIndex = usedImages.Count;

                        for (int i = 0; ; i++)
                        {
                            string key = string.Format("{0}-{1}", emitter.ShapeIndex, i);
                            if (sparks.Images.Find(key) != null)
                                usedImages.Add(key);
                            else
                                break;
                        }
                    }

                    int existsImageCount = usedImages.FindIndex(existsImageIndex + 1, (x) => !x.StartsWith(emitter.ShapeIndex.ToString()));
                    if (existsImageCount != -1)
                        existsImageCount = existsImageCount - existsImageIndex + 1;
                    else
                        existsImageCount = usedImages.Count - existsImageIndex;

                    if (existsImageCount == 1)
                        group["Image"] = existsImageIndex;
                    else
                        group["Image"] = MinMax(existsImageIndex, existsImageIndex + existsImageCount - 1);

                    if (emitter.IsLockAngle)
                        group["Angle"] = "Direction";
                    else
                    {
                        var angleOffset = MathExtension.DegreeToRadian(emitter.AngleOffset);
                        switch (emitter.AngleType)
                        {
                            case AngleType.Align:
                                group["Angle"] = "Emission";
                                group["AngleOffset"] = angleOffset;
                                break;
                            case AngleType.Random:
                                // 방출 방향에서 무작위 회전일지도 모릅니다. (어차피 눈치 채기는 힘들겠지만..)
                                group["Angle"] = MinMax(0.0f, angleOffset);
                                break;
                            case AngleType.Specify:
                                group["Angle"] = angleOffset;
                                break;
                        }
                    }

                    // TODO
                    group["IsRelativePosition"] = emitter.IsRelative;
                    group["IsRelativeAngle"] = emitter.IsAngleRelative;

                    spark[groupIndex++] = group;
                }

                var images = new Dict();
                for (int i = 0; i < usedImages.Count; i++)
                    images[i + 1] = usedImages[i];
                spark["Images"] = images;


                spark["Extra"] = new Dict()
                {
                    { "Length", effect.Length / 1000.0f },
                };

                sparks.Sparks.Add(effect.Name, new Spark(ToLuaTable(spark, 4)));
            }
        }

        private static bool AlmostEquals(float a, float b)
        {
            return Math.Abs(a - b) < float.Epsilon;
        }

        private static bool AlmostEquals(double a, double b)
        {
            return Math.Abs(a - b) < double.Epsilon;
        }

        private static bool IsValidMass(object mass)
        {
            if (mass == null)
                return false;

            if (mass is float)
                return ((float)mass) > 0.0f;
            else if (mass is double)
                return ((double)mass) > 0.0;

            return true;
        }

        private static float GetFirstValue(Graph graph, float defaultValue = 0.0f)
        {
            if (graph != null && graph.Count > 0)
                return graph[0].Value;
            else
                return defaultValue;
        }

        private static float? GetSingleValueOrNull(Graph graph, float defaultValue = 0.0f)
        {
            if (graph == null || graph.Count == 0)
                return defaultValue; // 그래프가 비어있을 경우
            else if (graph.Count == 1)
                return graph[0].Value;
            else
                return null; // 그래프에 여러 값이 있을 경우
        }

        private static object FloatGraphToValue(Graph baseGraph, Graph variationGraph, Graph overtimeGraph, Graph globalGraph, Func<float, float> transform = null)
        {
            var singleBase = GetSingleValueOrNull(baseGraph);
            var singleVariation = GetSingleValueOrNull(variationGraph, 0.0f);
            var singleOvertime = GetSingleValueOrNull(overtimeGraph, 1.0f);
            var singleGlobal = GetSingleValueOrNull(globalGraph, 1.0f);

            var emitterChangedByTime = !(singleBase.HasValue && singleVariation.HasValue && singleGlobal.HasValue);
            var particleChangedByTime = singleOvertime.HasValue == false;

            if (emitterChangedByTime && particleChangedByTime)
            {
                // Emitter와 Particle 모두 시간에 따라 고유 값이 바뀌는 구조
                // Spark Particle Engine 구조상 구현이 불가능합니다.
                Trace.TraceWarning("Base/Variation/Global와 Overtime이 동시에 그래프 구조를 가질 순 없습니다.");
                return null;
            }
            else if (emitterChangedByTime && particleChangedByTime == false)
            {
                // Emitter들은 시간에 따라 고유 값이 바뀌고 Particle들은 방출된 이후 고유 값을 유지하는 구조.
                return FloatGraphToValue(baseGraph, variationGraph, singleOvertime.Value, globalGraph, transform);
            }
            else if (emitterChangedByTime == false && particleChangedByTime)
            {
                // Emitter들은 고유 값을 유지하고 Particle들은 방출된 이후 고유 값이 바뀌는 구조.
                return FloatGraphToValue(singleBase.Value, singleVariation.Value, overtimeGraph, singleGlobal.Value, transform);
            }
            else
            {
                Trace.Assert(emitterChangedByTime == false && particleChangedByTime == false);
                // Emitter와 Particle 모두 고유 값을 유지하는 구조.
                return FloatToValue(singleBase.Value, singleVariation.Value, singleOvertime.Value, singleGlobal.Value, transform);
            }
        }

        private static object FloatGraphToValue(float baseValue, float variation, Graph overtime, float global, Func<float, float> transform = null)
        {
            var d = new Dict(overtime.Count + 1) { { "XAxis", "Lifetime" } };

            foreach (var item in overtime)
                d[item.Time] = FloatToValue(baseValue, variation, item.Value, global, transform);

            return d;
        }

        private static object FloatGraphToValue(Graph baseValue, Graph variation, float overtime, Graph global, Func<float, float> transform = null)
        {
            Graph min = new Graph(baseValue);
            Graph max = new Graph(baseValue);

            min = Graph.Merge(min, variation, (a, b) => a - b);
            max = Graph.Merge(max, variation, (a, b) => a + b);
            min = Graph.Merge(min, global, (a, b) => a * b);
            max = Graph.Merge(max, global, (a, b) => a * b);
            min.Transform((x) => transform(x * overtime));
            max.Transform((x) => transform(x * overtime));

            var d = new Dict(min.Count + 1) { { "XAxis", "Lifetime" } };

            for (int i = 0; i < min.Count; i++)
            {
                var time = min[i].Time;
                var minValue = min[i].Value;
                var maxValue = max[i].Value;
                if (AlmostEquals(minValue, maxValue))
                    d[time] = minValue;
                else
                    d[time] = MinMax(minValue, maxValue);
            }

            return d;
        }

        /// <summary>
        /// 그래프를 변환할 때 단일 값, 범위 값으로 강제하고 싶을 때 사용하면 됩니다.
        /// </summary>
        /// <param name="baseValue"></param>
        /// <param name="variation"></param>
        /// <param name="overtime"></param>
        /// <param name="global"></param>
        /// <returns></returns>
        private static object FloatToValue(Graph baseValue, Graph variation, Graph overtime, Graph global, Func<float, float> transform = null)
        {
            return FloatToValue(GetFirstValue(baseValue), GetFirstValue(variation, 0.0f), GetFirstValue(overtime, 1.0f), GetFirstValue(global, 1.0f), transform);
        }

        private static object FloatToValue(float baseValue, float variation = 0.0f, float overtime = 1.0f, float global = 1.0f, Func<float, float> transform = null)
        {
            if (transform == null)
                transform = (x) => x;

            if (AlmostEquals(variation, 0.0f))
                return transform(baseValue) * overtime * global;
            else
            {
                float min = transform(baseValue);
                float max = min;

                min -= transform(variation);
                max += transform(variation);

                min *= overtime * global;
                max *= overtime * global;

                return MinMax(min, max);
            }
        }

        private static object ColorGraphToValue(Graph graph)
        {
            var singleValue = GetSingleValueOrNull(graph, 255.0f);
            if (singleValue.HasValue && AlmostEquals(singleValue.Value, 255.0f))
                return null;
            else
                return FloatGraphToValue(new Graph() { new Keyframe(0.0f, 1.0f) }, null, graph, null, (x) => x / 255.0f);
        }

        private static string MinMax(object min, object max)
        {
            return string.Format("{0}~{1}", min, max);
        }

        private static Graph ReadGraph(IEnumerable<XElement> elements)
        {
            var data = new Graph(elements.Count());
            foreach (var item in elements)
            {
                float time = (float)item.Attribute("FRAME");
                float value = (float)item.Attribute("VALUE");
                data.Add(new Keyframe(time, value));
            }
            data.Sort((a, b) => a.Time.CompareTo(b.Time));

            if (data.Count == 2 && AlmostEquals(data[0].Value, data[1].Value))
                data.RemoveAt(1);

            if (data.Count == 1)
                data[0] = new Keyframe(0.0f, data[0].Value);

            return data;
        }

        private static string GetEffectFullName(XElement element)
        {
            return element
                .Ancestors("FOLDER")
                .Aggregate(
                    ((string)element.Attribute("NAME")).Trim(),
                    (name, item) => (string)item.Attribute("NAME") + "/" + name.Trim()
                )
                .Replace(' ', '-');
        }

        private static Dict LuaArray(params object[] args)
        {
            var d = new Dict(args.Length);
            var i = 1;
            foreach (var item in args)
                d[i++] = item;

            return d;
        }

        private static string ToLuaTable(Dict dict, int indent = 0)
        {
            var sb = new StringBuilder();
            Stringify(sb, dict, indent, 1);
            return sb.ToString();
        }

        private static void Stringify(StringBuilder sb, Dict dict, int indent = 0, int depth = 1)
        {
            var indentation = new string(' ', indent * depth);
            var prettyPrint = indent > 0;
            var crlf = prettyPrint ? "\n" : "";

            sb.Append('{');
            sb.Append(crlf);

            Action<object> stringify = (o) =>
            {
                if (o is string)
                    sb.Append(string.Format("\"{0}\"", o.ToString()));
                else if (o is Dict)
                    Stringify(sb, (Dict)o, indent, depth + 1);
                else
                    sb.Append(o.ToString());
            };

            foreach (var item in dict)
            {
                if (item.Value == null)
                    continue;

                sb.Append(indentation);

                if (item.Key is string)
                    sb.Append(item.Key.ToString());
                else
                {
                    sb.Append('[');
                    stringify(item.Key);
                    sb.Append(']');
                }

                if (prettyPrint)
                    sb.Append(" = ");
                else
                    sb.Append('=');

                stringify(item.Value);
                sb.Append(',');
                sb.Append(crlf);
            }

            sb.Append(new string(' ', indent * (depth - 1)));
            sb.Append('}');
        }
        #endregion
    }
}
