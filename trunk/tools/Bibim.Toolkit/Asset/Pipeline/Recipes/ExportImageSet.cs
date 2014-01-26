using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Text;
using Bibim.Graphics;
using Bibim.Json.Serialization;
using Bibim.UI;
using Bibim.UI.Visuals;
using Image = Bibim.Graphics.Image;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class ExportImageSet : ExportTemplate<ImageSet>
    {
        #region Constructors
        public ExportImageSet()
            : base()
        {
        }

        public ExportImageSet(CookingNode<ImageSet> input)
            : base(input)
        {
        }
        #endregion

        protected override void Export(CookingContext context, ImageSet input)
        {
            Export(context, input, BitmapSheetSize, BitmapSheetClusterSize, TextureOutput);
        }

        public static void Export(CookingContext context, ImageSet input, Size bitmapSheetSize, Size bitmapSheetClusterSize, string textureOutput)
        {
            var imageBitmaps = new Dictionary<Bitmap, List<Image>>();
            foreach (var item in input.Images)
            {
                var tag = (ImageCookingTag)item.Value.Tag;

                List<Image> values = null;
                if (imageBitmaps.TryGetValue(tag.Bitmap, out values))
                    values.Add(item.Value);
                else
                {
                    values = new List<Image>();
                    values.Add(item.Value);
                    imageBitmaps.Add(tag.Bitmap, values);
                }
            }

            using (var bitmapSheet = BitmapSheet.Create(imageBitmaps.Keys,
                                                        bitmapSheetSize.Width, bitmapSheetSize.Height,
                                                        bitmapSheetClusterSize.Width, bitmapSheetClusterSize.Height,
                                                        BitmapSheet.Options.PowerOfTwoSize | BitmapSheet.Options.RotatableMerging))
            {
                SaveTextureAssets(context, bitmapSheet, textureOutput, (source, textureURI, clippingRectangle, appliedTransform) =>
                {
                    List<Image> values = null;
                    if (imageBitmaps.TryGetValue(source, out values))
                    {
                        foreach (Image image in values)
                        {
                            image.TextureURI = textureURI;
                            image.ClippingRectangle = clippingRectangle;
                            image.AppliedTransform = appliedTransform;
                        }
                    }
                });
            }
        }

        public static void SaveTextureAssets(CookingContext context, BitmapSheet bitmapSheet, string textureOutput, Action<Bitmap, string, Rectangle, Image.Transform> f)
        {
            SaveTextureAssets(context, bitmapSheet.Sheets, textureOutput, true);

            foreach (BitmapSheet.Element item in bitmapSheet.Elements)
            {
                string textureURI = Path.Combine(context.Directory, Path.ChangeExtension((string)item.Sheet.Tag, null));
                var clippingRectangle = new Rectangle(item.Bounds.X, item.Bounds.Y,
                                                      item.Bounds.Width, item.Bounds.Height);
                var appliedTransform = item.AppliedTransform;

                f(item.Source, textureURI, clippingRectangle, appliedTransform);
            }
        }

        public static void SaveTextureAssets(CookingContext context, IEnumerable<Bitmap> textures, string textureOutput, bool taggingEnabled)
        {
            string absoluteDirectory = Path.Combine(context.BaseDirectory, context.Directory);
            if (Directory.Exists(absoluteDirectory) == false)
                Directory.CreateDirectory(absoluteDirectory);

            int textureNumber = 0;
            string textureOutputFormat = context.ExpandVariables(textureOutput);
            foreach (Bitmap item in textures)
            {
                Trace.Assert(item.Tag == null); // 밑에서 Tag를 직접 사용할 것이기 때문에 확인합니다.

                string path = string.Format(textureOutputFormat, textureNumber++);

                string textureFilePath = Path.ChangeExtension(path, "png");
                string fullPath = Path.Combine(absoluteDirectory, textureFilePath);
                string fullPathDirectory = Path.GetDirectoryName(fullPath);
                if (Directory.Exists(fullPathDirectory) == false)
                    Directory.CreateDirectory(fullPathDirectory);

                item.Save(fullPath, ImageFormat.Png);
                if (taggingEnabled)
                    item.Tag = textureFilePath;

                using (var fs = new FileStream(Path.ChangeExtension(fullPath, "asset"), FileMode.Create, FileAccess.Write))
                {
                    // png 파일은 자동 추론 되기 때문에 그냥 빈 파일만 생성합니다.
                }
            }
        }
    }
}
