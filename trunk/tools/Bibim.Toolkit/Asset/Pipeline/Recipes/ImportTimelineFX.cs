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
using Graph = System.Collections.Generic.List<System.Tuple<float, float>>;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class ImportTimelineFX : CookingNode<SparkSet>
    {
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
                    sparks.Images.Images.Add(index.ToString(), new Image(string.Empty, Rectangle.Empty)
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
            foreach (var effectElement in doc.Descendants("EFFECT"))
            {
                Dict spark = new Dict();

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
                    GlobalAlpha = ReadGraph(effectElement.Elements("ALPHA")), //----------//
                    GlobalStretch = ReadGraph(effectElement.Elements("STRETCH")), //----------//
                    EffectEmissionRange = ReadGraph(effectElement.Elements("EMISSIONRANGE")), //----------//
                    EffectEmissionAngle = ReadGraph(effectElement.Elements("EMISSIONANGLE")), //----------//
                    AreaWidth = ReadGraph(effectElement.Elements("AREA_WIDTH")), //----------//
                    AreaHeight = ReadGraph(effectElement.Elements("AREA_HEIGHT")), //----------//
                    EffectAngle = ReadGraph(effectElement.Elements("ANGLE")), //----------//
                };

                var groupIndex = 1;
                foreach (var emitterElement in effectElement.Elements("PARTICLE").OrderBy((e)=>(int)e.Attribute("LAYER")))
                {
                    var emitter = new
                    {
                        // HandleX = (int)emitterElement.Attribute("HANDLE_X"),
                        // HandleY = (int)emitterElement.Attribute("HANDLE_Y"),
                        // BlendMode = (int)emitterElement.Attribute("BLENDMODE"),
                        IsRelative = (bool)emitterElement.Attribute("RELATIVE"), //----------//
                        IsRandomColor = (bool)emitterElement.Attribute("RANDOM_COLOR"), //----------//
                        IsSingleParticle = (bool)emitterElement.Attribute("SINGLE_PARTICLE"), //----------//
                        // Layer = (int)emitterElement.Attribute("LAYER"),
                        // Name = (string)emitterElement.Attribute("NAME"),
                        IsAnimate = (bool)emitterElement.Attribute("ANIMATE"), //----------//
                        IsAnimateOnce = (bool)emitterElement.Attribute("ANIMATE_ONCE"), //----------//
                        Frame = (int)emitterElement.Attribute("FRAME"), //----------//
                        RandomStartFrame = (int)emitterElement.Attribute("RANDOM_START_FRAME"), //----------//
                        IsAnimateForwardDirection = (bool)emitterElement.Attribute("ANIMATION_DIRECTION"), //----------//
                        IsUniform = (bool)emitterElement.Attribute("UNIFORM"), //----------//
                        AngleType = (AngleType)(int)emitterElement.Attribute("ANGLE_TYPE"), //----------//
                        AngleOffset = (int)emitterElement.Attribute("ANGLE_OFFSET"), //----------//
                        IsLockAngle = (bool)emitterElement.Attribute("LOCK_ANGLE"), //----------//
                        IsAngleRelative = (bool)emitterElement.Attribute("ANGLE_RELATIVE"), //----------//
                        IsEffectEmissionUsed = (bool)emitterElement.Attribute("USE_EFFECT_EMISSION"), //----------//
                        ColorRepeat = (int)emitterElement.Attribute("COLOR_REPEAT"), //----------//
                        AlphaRepeat = (int)emitterElement.Attribute("ALPHA_REPEAT"), //----------//
                        IsOneShot = (bool)emitterElement.Attribute("ONE_SHOT"), //----------//
                        // IsHandleCentered = (bool)emitterElement.Attribute("HANDLE_CENTERED"),
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
                        ScaleXOvertime = ReadGraph(emitterElement.  Elements("SCALE_X_OVERTIME")),
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
                    };

                    var groupEmitter = new Dict()
                    {
                        { "Flow", 100 }, //SingleGraphToValue(emitter.Amount, emitter.AmountVariation, null, effect.GlobalAmount) },
                        { "Force", SingleGraphToValue(emitter.BaseSpeed, emitter.SpeedVariation, emitter.SpeedOvertime, effect.GlobalSpeed) },
                    };

                    switch (effect.Type)
                    {
                        case EffectType.Point:
                        case EffectType.Area:
                        case EffectType.Line:
                        case EffectType.Ring:
                            // effect.GridX;
                            // effect.GridY;
                            groupEmitter["Zone"] = new Dict() { { 1, 0 }, { 2, 0 } };
                            break;
                    }

                    var group = new Dict()
                    {
                        { "Red", ColorGraphToValue(emitter.RedOvertime) },
                        { "Green", ColorGraphToValue(emitter.GreenOvertime) },
                        { "Blue", ColorGraphToValue(emitter.BlueOvertime) },
                        { "Lifetime", SingleGraphToValue(emitter.Life, emitter.LifeVariation, null, effect.GlobalLife) },
                        { "Opacity", SingleGraphToValue(null, null, emitter.AlphaOvertime, effect.GlobalAlpha) },
                        { "SizeX", SingleGraphToValue(emitter.BaseSizeX, emitter.SizeXVariation, emitter.ScaleXOvertime, effect.GlobalSizeX) },
                        { "SizeY", SingleGraphToValue(emitter.BaseSizeY, emitter.SizeYVariation, emitter.ScaleYOvertime, effect.GlobalSizeY) },
                        { "Mass", SingleGraphToValue(emitter.BaseWeight, emitter.WeightVariation, emitter.WeightOvertime, effect.GlobalWeight) },
                        { "AngularSpeed", SingleGraphToValue(emitter.BaseSpin, emitter.SpinVariation, emitter.SpinOvertime, effect.GlobalSpin) },
                        { "Angle", "Direction" },
                        { "Image", 0 }, //----------//
                        { "Emitter", groupEmitter },
                    };
                    spark[groupIndex++] = group;
                }

                spark["Images"] = new Dict()
                {
                    { 1, sparks.Images.Images.First().Key },
                };

                spark["Extra"] = new Dict()
                {
                    { "Length", ((float)effect.Length) * 0.01f },
                };

                sparks.Sparks.Add(effect.Name, new Spark(ToLuaTable(spark, 4)));
            }
        }

        private static bool AlmostEquals(float a, float b)
        {
            return Math.Abs(a - b) < float.Epsilon;
        }

        private static bool IsDefaultValue(Graph graph, float value = 1.0f)
        {
            return (
                (graph.Count == 0) ||
                (graph.Count == 1 && AlmostEquals(graph[0].Item2, value))
            );
        }

        private static object SingleGraphToValue(Graph baseValue, Graph variation, Graph overtime, Graph global)
        {
            try
            {
                if (baseValue.Count == 1 && variation.Count <= 1 && global.Count <= 1 && (overtime == null || overtime.Count <= 1))
                {
                    // 가장 흔한 경우

                    float minValue = baseValue[0].Item2;
                    float maxValue = minValue;

                    if (variation.Count == 1 && AlmostEquals(variation[0].Item2, 0.0f) == false)
                    {
                        minValue -= variation[0].Item2;
                        maxValue += variation[0].Item2;
                    }

                    if (overtime != null && overtime.Count == 1 && AlmostEquals(overtime[0].Item2, 1.0f) == false)
                    {
                        minValue *= overtime[0].Item2;
                        maxValue *= overtime[0].Item2;
                    }

                    if (global.Count == 1 && AlmostEquals(global[0].Item2, 1.0f) == false)
                    {
                        minValue *= global[0].Item2;
                        maxValue *= global[0].Item2;
                    }

                    if (AlmostEquals(minValue, maxValue))
                        return minValue;
                    else
                        return string.Format("{0}~{1}", minValue, maxValue);
                }
            }
            catch (Exception)
            {
            }

            return 1.0f;
        }

        private static object ColorGraphToValue(Graph graph)
        {
            if (IsDefaultValue(graph, 255.0f) == false)
                return ToValue(graph, (x) => x / 255.0f);
            else
                return null;
        }

        private static object ToValue(Graph graph, Func<float, float> transform = null)
        {
            transform = transform ?? ((x) => x);

            if (graph.Count == 0)
                return null;
            else if (graph.Count == 1)
                return transform(graph[0].Item2);
            else
            {
                var d = new Dict(graph.Count + 1) {
                    { "XAxis", "Lifetime" },
                };

                foreach (var item in graph)
                {
                    var time = item.Item1;
                    var value = item.Item2;
                    d[time] = transform(value);
                }

                return d;
            }
        }

        private static Graph ReadGraph(IEnumerable<XElement> elements)
        {
            var data = new List<Tuple<float, float>>(elements.Count());
            foreach (var item in elements)
            {
                float time = (float)item.Attribute("FRAME");
                float value = (float)item.Attribute("VALUE");
                data.Add(Tuple.Create(time, value));
            }
            data.Sort((a, b) => a.Item1.CompareTo(b.Item1));

            if (data.Count == 2 && AlmostEquals(data[0].Item2, data[1].Item2))
                data.RemoveAt(1);

            if (data.Count == 1)
                data[0] = Tuple.Create(0.0f, data[0].Item2);

            return data;
        }

        private static string GetEffectFullName(XElement element)
        {
            return element
                .Ancestors("FOLDER")
                .Aggregate(
                    (string)element.Attribute("NAME"), 
                    (name, item) => (string)item.Attribute("NAME") + "/" + name
                )
                .Replace(' ', '-');
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
            var crlf = (indent > 0) ? "\n" : "";

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

                sb.Append(" = ");
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
