using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Text;
using Bibim.Animation;
using Bibim.Graphics;
using Bibim.Json.Serialization;
using Bibim.UI;
using Bibim.UI.Visuals;
using Sprite = Bibim.Animation.Sprite;
using Rectangle = Microsoft.Xna.Framework.Rectangle;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class ExportSpriteSet : ExportTemplate<SpriteSet>
    {
        #region Constructors
        public ExportSpriteSet()
            : base()
        {
        }

        public ExportSpriteSet(CookingNode<SpriteSet> input)
            : base(input)
        {
        }
        #endregion

        protected override void Export(CookingContext context, SpriteSet input)
        {
            var spriteBitmaps = new Dictionary<Bitmap, List<Tuple<Sprite, int>>>();
            foreach (var item in input.Sprites)
            {
                var tag = (SpriteCookingTag)item.Value.Tag;
                for (int i = 0; i < tag.Bitmaps.Count; i++)
                {
                    Bitmap bitmap = tag.Bitmaps[i];
                    List<Tuple<Sprite, int>> values = null;
                    if (spriteBitmaps.TryGetValue(bitmap, out values))
                        values.Add(Tuple.Create(item.Value, i));
                    else
                    {
                        values = new List<Tuple<Sprite, int>>();
                        values.Add(Tuple.Create(item.Value, i));
                        spriteBitmaps.Add(bitmap, values);
                    }
                }
            }

            using (var bitmapSheet = BitmapSheet.Create(spriteBitmaps.Keys,
                                                        BitmapSheetSize.Width, BitmapSheetSize.Height,
                                                        BitmapSheetClusterSize.Width, BitmapSheetClusterSize.Height,
                                                        BitmapSheet.Options.PowerOfTwoSize | BitmapSheet.Options.RotatableMerging))
            {
                ExportImageSet.SaveTextureAssets(context, bitmapSheet, TextureOutput, (source, textureURI, clippingRectangle, appliedTransform) =>
                {
                    List<Tuple<Sprite, int>> values = null;
                    if (spriteBitmaps.TryGetValue(source, out values))
                    {
                        foreach (var item in values)
                        {
                            item.Item1.Keyframes[item.Item2].TextureURI = textureURI;
                            item.Item1.Keyframes[item.Item2].ClippingRectangle = clippingRectangle;
                            item.Item1.Keyframes[item.Item2].AppliedTransform = appliedTransform;
                        }
                    }
                });
            }
        }
    }
}
