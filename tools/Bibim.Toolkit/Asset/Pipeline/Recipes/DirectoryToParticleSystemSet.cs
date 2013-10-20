using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.IO.Compression;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Xml.Linq;
using Microsoft.Xna.Framework;
using Bibim.GFX;
using Bibim.Graphics;
using Bibim.UI;
using Bibim.UI.Effects;
using Bibim.UI.Events;
using Bibim.UI.Visuals;
using Image = Bibim.Graphics.Image;
using Rectangle = Microsoft.Xna.Framework.Rectangle;
using GDIColor = System.Drawing.Color;

namespace Bibim.Asset.Pipeline.Recipes
{
    public class DirectoryToParticleSystemSet : CookingNode<ParticleSystemSet>
    {
        #region Properties
        public string Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public DirectoryToParticleSystemSet()
            : this(string.Empty)
        {
        }

        public DirectoryToParticleSystemSet(string input)
        {
            Input = input;
        }
        #endregion

        public override ParticleSystemSet Cook(CookingContext context)
        {
            string actualPath = Path.Combine(context.BaseDirectory, context.Directory, context.ExpandVariables(Input));

            Dictionary<string, ParticleSystem> items = new Dictionary<string, ParticleSystem>();
            foreach (var item in Directory.GetFiles(actualPath, "*.plist", SearchOption.TopDirectoryOnly))
            {
                string name = Path.GetFileNameWithoutExtension(item);
                var o = Bibim.Xml.XmlExtension.LoadPList(item);

                Func<string, bool> b = (key) => o.ContainsKey(key) ? Convert.ToBoolean(o[key], CultureInfo.InvariantCulture) : false;
                Func<string, int> i = (key) => o.ContainsKey(key) ? Convert.ToInt32(o[key], CultureInfo.InvariantCulture) : 0;
                Func<string, float> f = (key) => o.ContainsKey(key) ? Convert.ToSingle(o[key], CultureInfo.InvariantCulture) : 0.0f;
                Func<string, string, Vector2> v2 = (k1, k2) => new Vector2(f(k1), f(k2));
                Func<string, string, string, string, Vector4> v4 = (k1, k2, k3, k4) => new Vector4(f(k1), f(k2), f(k3), f(k4));
                var system = new ParticleSystem()
                {
                    Angle = f("angle"),
                    AngleVariance = f("angleVariance"),
                    BlendFunctionDestination = i("blendFuncDestination"),
                    BlendFunctionSource = i("blendFuncSource"),
                    Duration = f("duration"),
                    Mode = (ParticleSystem.EmitterMode)i("emitterType"),
                    FinishColor = v4("finishColorRed", "finishColorGreen", "finishColorBlue", "finishColorAlpha"),
                    FinishColorVariance = v4("finishColorVarianceRed", "finishColorVarianceGreen", "finishColorVarianceBlue", "finishColorVarianceAlpha"),
                    FinishParticleRotation = f("rotationEnd"),
                    FinishParticleRotationVariance = f("rotationEndVariance"),
                    FinishParticleSize = f("finishParticleSize"),
                    FinishParticleSizeVariance = f("finishParticleSizeVariance"),
                    Gravity = v2("gravityx", "gravityy"),
                    MaxParticles = i("maxParticles"),
                    MaxRadius = f("maxRadius"),
                    MaxRadiusVariance = f("maxRadiusVariance"),
                    MinRadius = f("minRadius"),
                    ParticleLifespan = f("particleLifespan"),
                    ParticleLifespanVariance = f("particleLifespanVariance"),
                    RadialAccelVariance = f("radialAccelVariance"),
                    RadialAcceleration = f("radialAcceleration"),
                    Spin = f("rotatePerSecond"),
                    SpinVariance = f("rotatePerSecondVariance"),
                    RotationIsDirection = b("rotationIsDir"),
                    SourcePosition = v2("sourcePositionx", "sourcePositiony"),
                    SourcePositionVariance = v2("sourcePositionVariancex", "sourcePositionVariancey"),
                    Speed = f("speed"),
                    SpeedVariance = f("speedVariance"),
                    StartColor = v4("startColorRed", "startColorGreen", "startColorBlue", "startColorAlpha"),
                    StartColorVariance = v4("startColorVarianceRed", "startColorVarianceGreen", "startColorVarianceBlue", "startColorVarianceAlpha"),
                    StartParticleRotation = f("rotationStart"),
                    StartParticleRotationVariance = f("rotationStartVariance"),
                    StartParticleSize = f("startParticleSize"),
                    StartParticleSizeVariance = f("startParticleSizeVariance"),
                    TangentialAccelVariance = f("tangentialAccelVariance"),
                    TangentialAcceleration = f("tangentialAcceleration"),
                };

                var textureImageData = (string)o["textureImageData"];
                using (var stream = new MemoryStream(Convert.FromBase64String(textureImageData)))
                using (var s = new GZipStream(stream, CompressionMode.Decompress))
                {
                    var bitmap = new Bitmap(s);
                    system.Image = new Image(string.Empty, Rectangle.Empty)
                    {
                        Tag = new ImageCookingTag(bitmap),
                    };

                    var dim = (float)Math.Min(bitmap.Width, bitmap.Height);
                    system.StartParticleSize /= dim;
                    system.StartParticleSizeVariance /= dim;
                    system.FinishParticleSize /= dim;
                    system.FinishParticleSizeVariance /= dim;
                }

                items.Add(name, system);
            }

            return new ParticleSystemSet(items);
        }
    }
}
