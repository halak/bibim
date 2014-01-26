using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Text;
using Microsoft.Xna.Framework;
using Bibim.Animation;
using Bibim.Graphics;
using Bibim.UI;
using Bibim.UI.Effects;
using Bibim.UI.Events;
using Bibim.UI.Visuals;
using Image = Bibim.Graphics.Image;
using GDIColor = System.Drawing.Color;

namespace Bibim.Asset.Pipeline.Recipes
{
    public class PhotoshopDocumentToSpriteSet : CookingNode<SpriteSet>
    {
        #region Properties
        public CookingNode<PhotoshopDocument> Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public PhotoshopDocumentToSpriteSet()
            : this(null)
        {
        }

        public PhotoshopDocumentToSpriteSet(CookingNode<PhotoshopDocument> input)
        {
            Input = input;
        }
        #endregion

        public override SpriteSet Cook(CookingContext context)
        {
            PhotoshopDocument input = Input.Cook(context);
            var items = new Dictionary<string, Sprite>();

            foreach (var item in input.Layers)
            {
                if (item.IsGroup)
                    Process(items, item, string.Empty);
                else
                {
                    // 최상위 Layer에서 그룹이 아닌 레이어는 무시합니다.
                }
            }

            return new SpriteSet(items);
        }

        private void Process(Dictionary<string, Sprite> items, PhotoshopDocument.Layer layer, string prefix)
        {
            string name = layer.Name;
            if (name.StartsWith("#"))
                name = name.Substring(1);
            if (string.IsNullOrEmpty(prefix) == false)
                name = string.Format("{0}/{1}", prefix, layer.Name);

            foreach (var item in layer.SubLayers)
            {
                if (item.IsGroup)
                    Process(items, item, name);
            }

            if (layer.Name.StartsWith("#"))
            {
                List<Sprite.Keyframe> keyframes = null;
                List<Bitmap> bitmaps = null;
                foreach (var item in layer.SubLayers)
                {
                    if (item.IsGroup == false)
                    {
                        keyframes = keyframes ?? new List<Sprite.Keyframe>();
                        bitmaps = bitmaps ?? new List<Bitmap>();

                        keyframes.Add(new Sprite.Keyframe()
                        {
                            TextureURI = string.Empty,
                            ClippingRectangle = Rectangle.Empty,
                            AppliedTransform = Image.Transform.Identity,
                            Origin = Vector2.Zero,
                            Duration = 0.075f,
                        });
                        bitmaps.Add(item.Bitmap);
                    }
                }

                if (keyframes != null && bitmaps != null && keyframes.Count > 0 && bitmaps.Count > 0)
                {
                    // keyframes.Reverse();
                    // bitmaps.Reverse();

                    items.Add(name, new Sprite(keyframes)
                    {
                        BlendMode = BlendMode.Normal,
                        Tag = new SpriteCookingTag(bitmaps)
                    });
                }
            }
        }
    }
}
