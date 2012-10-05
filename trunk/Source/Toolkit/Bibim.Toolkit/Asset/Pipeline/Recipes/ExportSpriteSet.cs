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
    public sealed class ExportSpriteSet : CookingNode<SpriteSet>
    {
        #region Fields
        private string textureOutput;
        #endregion

        #region Properties
        public CookingNode<SpriteSet> Input
        {
            get;
            set;
        }

        public Size BitmapSheetSize
        {
            get;
            set;
        }

        public Size BitmapSheetClusterSize
        {
            get;
            set;
        }

        public string TextureOutput
        {
            get { return textureOutput; }
            set
            {
                textureOutput = value ?? string.Empty;
            }
        }
        #endregion

        #region Constructors
        public ExportSpriteSet()
            : this(null)
        {
        }

        public ExportSpriteSet(CookingNode<SpriteSet> input)
        {
            Input = input;
            BitmapSheetSize = new Size(1024, 1024);
            BitmapSheetClusterSize = new Size(16, 16);
            textureOutput = "$(AssetName)_TEX{0}";
        }
        #endregion

        public override SpriteSet Cook(CookingContext context)
        {
            if (BitmapSheetSize.IsEmpty)
                throw new InvalidOperationException("BitmapSheetSize is empty.");
            if (string.IsNullOrEmpty(TextureOutput))
                throw new InvalidOperationException("TextureOutput is null.");
            if (TextureOutput.Contains("{0}") == false)
                throw new InvalidOperationException("TextureOutput not exists {0}.");

            SpriteSet input = Input.Cook(context);

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
                ExportImageSet.SaveTextureAssets(context, bitmapSheet, textureOutput, (source, textureURI, clippingRectangle, appliedTransform) =>
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

            return input;
        }
    }
}
