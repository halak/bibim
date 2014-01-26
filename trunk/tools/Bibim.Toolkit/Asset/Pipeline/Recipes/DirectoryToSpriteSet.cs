using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Bibim.Animation;
using Bibim.Graphics;
using Bibim.Json.Serialization;
using Bibim.UI;
using Bibim.UI.Effects;
using Bibim.UI.Events;
using Bibim.UI.Visuals;
using Image = Bibim.Graphics.Image;
using Color = System.Drawing.Color;

namespace Bibim.Asset.Pipeline.Recipes
{
    public class DirectoryToSpriteSet : CookingNode<SpriteSet>
    {
        #region Properties
        public string Input
        {
            get;
            set;
        }

        public Size UniformSize
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public DirectoryToSpriteSet()
            : this(string.Empty, Size.Empty)
        {
        }

        public DirectoryToSpriteSet(string input)
            : this(input, Size.Empty)
        {
        }

        public DirectoryToSpriteSet(string input, Size uniformSize)
        {
            this.Input = input;
            this.UniformSize = uniformSize;
        }
        #endregion

        public override SpriteSet Cook(CookingContext context)
        {
            string actualPath = Path.Combine(context.BaseDirectory, context.Directory, context.ExpandVariables(Input));

            var items = new Dictionary<string, Sprite>();
            foreach (var item in Directory.GetFiles(actualPath))
            {
                string name = Path.GetFileNameWithoutExtension(item);
                string extension = Path.GetExtension(item);
                Sprite sprite = null;
                switch (extension.ToLower())
                {
                    case ".strip":
                        sprite = CreateFromStrip(context, item);
                        break;
                    case ".celanim":
                        sprite = CreateFromCelAnimation(context, item);
                        break;
                    default:
                        sprite = null;
                        break;
                }

                if (sprite != null)
                {
                    context.AddDependency(item);
                    items.Add(name, sprite);
                }
            }

            return new SpriteSet(items);
        }

        private Sprite CreateFromStrip(CookingContext context, string path)
        {
            var name = Path.GetFileNameWithoutExtension(path);
            var directory = Path.GetDirectoryName(path);
            var bitmapPath1 = Path.Combine(directory, string.Format("{0}.png", name));
            var bitmapPath2 = Path.Combine(directory, string.Format("{0}.bmp", name));
            var bitmapPath3 = Path.Combine(directory, string.Format("{0}.jpg", name));
            Bitmap bitmap = BitmapExtension.CreateOne(bitmapPath1, bitmapPath2, bitmapPath3);
            if (bitmap == null)
                return null;

            context.AddDependency(bitmapPath1);
            context.AddDependency(bitmapPath2);
            context.AddDependency(bitmapPath3);

            var data = JsonSerializer.DeserializeDataFromFile(path) as Dictionary<string, object>;
            var frames = data.Get("frames", 0);
            var size = data.Get("size", Size.Empty);
            var sprite = CreateSprite(EnumerateStrip(bitmap, frames, size), data);
            bitmap.Dispose();

            return sprite;
        }

        private Sprite CreateFromCelAnimation(CookingContext context, string path)
        {
            var name = Path.GetFileNameWithoutExtension(path);
            var directory = Path.GetDirectoryName(path);
            var celsPath = Path.Combine(directory, name);
            if (Directory.Exists(celsPath) == false)
                return null;

            var data = JsonSerializer.DeserializeDataFromFile(path) as Dictionary<string, object>;
            return CreateSprite(EnumerateCels(celsPath), data);
        }

        private IEnumerable<Bitmap> EnumerateStrip(Bitmap bitmap, int frames, Size size)
        {
            if (size.Width > 0 && size.Height > 0)
            {
                int columns = bitmap.Width / size.Width;
                for (int i = 0; i < frames; i++)
                {
                    var clip = new Rectangle(i % columns * size.Width,
                                             i / columns * size.Height,
                                             size.Width,
                                             size.Height);
                    yield return bitmap.Clip(clip);
                }
            }
        }

        private IEnumerable<Bitmap> EnumerateCels(string directory)
        {
            var q = Directory.EnumerateFiles(directory, "*.*", SearchOption.TopDirectoryOnly);
            foreach (var item in q.OrderBy(x => x))
            {
                var bitmap = BitmapExtension.CreateOne(item);
                if (bitmap != null)
                    yield return bitmap;
            }
        }

        private Sprite CreateSprite(IEnumerable<Bitmap> frames, Dictionary<string, object> data)
        {
            var interval = data.Get("interval", 0.075f);
            var loop = data.Get("loop", false);
            var blendMode = data.Get("blend", BlendMode.Additive);

            var keyframes = new List<Sprite.Keyframe>();
            var bitmaps = new List<Bitmap>();

            var trimmingColor = (blendMode == BlendMode.Normal) ? Color.Transparent : Color.Black;
            foreach (var originalFrame in frames)
            {
                var frame = originalFrame;
                var origin = new Vector2(frame.Width / 2, frame.Height / 2);
                var trimmedRect = frame.GetTrimmedRect(trimmingColor);
                if (trimmedRect.Width != frame.Width || trimmedRect.Height != frame.Height)
                {
                    frame = frame.ClipAndDispose(trimmedRect);
                    origin.X -= trimmedRect.X;
                    origin.Y -= trimmedRect.Y;
                }

                keyframes.Add(new Sprite.Keyframe()
                {
                    TextureURI = string.Empty,
                    ClippingRectangle = Rectangle.Empty,
                    AppliedTransform = Image.Transform.Identity,
                    Origin = origin,
                    Duration = interval,
                });
                bitmaps.Add(frame);
            }

            if (keyframes.Count > 0 && bitmaps.Count > 0)
            {
                return new Sprite(keyframes)
                {
                    BlendMode = blendMode,
                    Loop = loop,
                    Tag = new SpriteCookingTag(bitmaps)
                };
            }
            else
                return null;
        }
    }
}
