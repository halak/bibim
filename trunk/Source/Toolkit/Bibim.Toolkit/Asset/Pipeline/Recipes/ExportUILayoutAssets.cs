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
using Rectangle = Microsoft.Xna.Framework.Rectangle;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class ExportUILayoutAssets : CookingNode<UILayout>
    {
        #region Fields
        private string textureOutput;
        private string imageOutput;
        private string maskOutput;
        #endregion

        #region Properties
        public CookingNode<UILayout> Input
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

        public string ImageOutput
        {
            get { return imageOutput; }
            set
            {
                imageOutput = value ?? string.Empty;
            }
        }

        public string MaskOutput
        {
            get { return maskOutput; }
            set
            {
                maskOutput = value ?? string.Empty;
            }
        }
        #endregion

        #region Constructors
        public ExportUILayoutAssets()
            : this(null)
        {
        }

        public ExportUILayoutAssets(CookingNode<UILayout> input)
        {
            Input = input;
            BitmapSheetSize = new Size(1024, 1024);
            BitmapSheetClusterSize = new Size(16, 16);
            textureOutput = "$(AssetName)_TEX{0}";
            imageOutput = "$(AssetName)_IMG{0}";
            maskOutput = "$(AssetName)_MSK{0}";
        }
        #endregion

        public override UILayout Cook(CookingContext context)
        {
            if (BitmapSheetSize.IsEmpty)
                throw new InvalidOperationException("BitmapSheetSize is empty.");
            if (string.IsNullOrEmpty(TextureOutput))
                throw new InvalidOperationException("TextureOutput is null.");
            if (TextureOutput.Contains("{0}") == false)
                throw new InvalidOperationException("TextureOutput not exists {0}.");
            if (string.IsNullOrEmpty(ImageOutput))
                throw new InvalidOperationException("ImageOutput is null.");
            if (ImageOutput.Contains("{0}") == false)
                throw new InvalidOperationException("ImageOutput not exists {0}.");

            UILayout input = Input.Cook(context);

            List<UIImage> images = new List<UIImage>();
            List<UILabel> labels = new List<UILabel>();
            CollectObjects(input.Root, images, labels);

            OptimizeAllImages(context, images);
            MergeAllImages(context, images);
            ExportAllMasks(context, images);

            return input;
        }

        private static void CollectObjects(UIVisual visual, List<UIImage> images, List<UILabel> labels)
        {
            if (visual is UIImage)
                images.Add((UIImage)visual);
            else if (visual is UILabel)
                labels.Add((UILabel)visual);
            else if (visual is UIPanel)
            {
                foreach (UIVisual item in ((UIPanel)visual).Children)
                    CollectObjects(item, images, labels);
            }
        }

        private void OptimizeAllImages(CookingContext context, ICollection<UIImage> images)
        {
            var uniqueImages = new List<Image>();
            foreach (var item in images)
            {
                bool found = false;
                foreach (var image in uniqueImages)
                {
                    if (EqualsImage(item.Source, image))
                    {
                        item.Source = image;
                        found = true;
                        break;
                    }
                }

                if (found == false)
                    uniqueImages.Add(item.Source);
            }
        }

        private static bool EqualsImage(Image a, Image b)
        {
            if (a == null || b == null)
                return false;

            var aTag = a.Tag as ImageCookingTag;
            var bTag = b.Tag as ImageCookingTag;

            if (aTag != null && aTag.Bitmap != null && bTag != null && bTag.Bitmap != null)
            {
                int aWidth = a.ClippingRectangle.Width;
                int aHeight = a.ClippingRectangle.Height;
                int bWidth = b.ClippingRectangle.Width;
                int bHeight = b.ClippingRectangle.Height;

                if (aWidth == 0)
                    aWidth = aTag.Bitmap.Width;
                if (aHeight == 0)
                    aHeight = aTag.Bitmap.Height;
                if (bWidth == 0)
                    bWidth = bTag.Bitmap.Width;
                if (bHeight == 0)
                    bHeight = bTag.Bitmap.Height;

                if (aWidth != bWidth ||
                    aHeight != bHeight)
                    return false;

                for (int y = 0; y < aHeight; y++)
                {
                    for (int x = 0; x < aWidth; x++)
                    {
                        Color aPixel = aTag.Bitmap.GetPixel(x + a.ClippingRectangle.X, y + a.ClippingRectangle.Y);
                        Color bPixel = bTag.Bitmap.GetPixel(x + b.ClippingRectangle.X, y + b.ClippingRectangle.Y);

                        if (aPixel.A > 0 && bPixel.A > 0)
                        {
                            if (aPixel != bPixel)
                                return false;
                        }
                        else
                        {
                            if (aPixel.A != 0 || bPixel.A != 0)
                                return false;
                        }
                    }
                }

                return true;
            }
            else
                return false;
        }

        private void MergeAllImages(CookingContext context, ICollection<UIImage> images)
        {
            var imageBitmaps = new Dictionary<Bitmap, List<UIImage>>(images.Count);
            foreach (var item in images)
            {
                var tag = item.Source.Tag as ImageCookingTag;
                if (tag != null && tag.Bitmap != null)
                {
                    List<UIImage> values = null;
                    if (imageBitmaps.TryGetValue(tag.Bitmap, out values))
                        values.Add(item);
                    else
                    {
                        values = new List<UIImage>() { item };
                        imageBitmaps.Add(tag.Bitmap, values);
                    }
                }
            }

            using (var bitmapSheet = BitmapSheet.Create(imageBitmaps.Keys,
                                                        BitmapSheetSize.Width, BitmapSheetSize.Height,
                                                        BitmapSheetClusterSize.Width, BitmapSheetClusterSize.Height,
                                                        BitmapSheet.Options.PowerOfTwoSize | BitmapSheet.Options.RotatableMerging))
            {
                #region Texture File과 Asset을 저장합니다.
                var textureFileToStream = new FileToStream();
                var textureRecipe = new GameAssetRecipe()
                {
                    Cook = new BitmapToTexture2D(new ImportBitmap(textureFileToStream)),
                    Author = GetType().FullName,
                    Comment = "Automatically generated.",
                };

                string absoluteDirectory = Path.Combine(context.BaseDirectory, context.Directory);
                if (Directory.Exists(absoluteDirectory) == false)
                    Directory.CreateDirectory(absoluteDirectory);

                int textureNumber = 0;
                string textureOutputFormat = context.ExpandVariables(TextureOutput);
                foreach (Bitmap item in bitmapSheet.Sheets)
                {
                    Trace.Assert(item.Tag == null); // 밑에서 Tag를 직접 사용할 것이기 때문에 확인합니다.

                    string path = string.Format(textureOutputFormat, textureNumber++);

                    string textureFilePath = Path.ChangeExtension(path, "png");
                    string fullPath = Path.Combine(absoluteDirectory, textureFilePath);
                    string fullPathDirectory = Path.GetDirectoryName(fullPath);
                    if (Directory.Exists(fullPathDirectory) == false)
                        Directory.CreateDirectory(fullPathDirectory);

                    item.Save(fullPath, ImageFormat.Png);
                    item.Tag = textureFilePath;

                    textureFileToStream.Input1 = Path.GetFileName(textureFilePath);

                    JsonSerializer.Instance.Serialize(Path.ChangeExtension(fullPath, "asset"), textureRecipe);
                }
                #endregion

                #region Image Asset을 저장합니다
                // EMBEDDED UIIMAGE
                /*
                var readImage = new ReadGameAsset();
                var imageRecipe = new GameAssetRecipe()
                {
                    Cook = readImage,
                    Author = GetType().FullName,
                    Comment = "Automatically generated.",
                };
                */

                int imageNumber = 0;
                string imageOutputFormat = context.ExpandVariables(ImageOutput);
                foreach (BitmapSheet.Element item in bitmapSheet.Elements)
                {
                    string textureURI = Path.Combine(context.Directory, Path.ChangeExtension((string)item.Sheet.Tag, null));
                    /*
                    string path = string.Format(imageOutputFormat, imageNumber++);

                    readImage.Input = new Image()
                    {
                        TextureURI = Path.Combine(context.Directory, Path.ChangeExtension((string)item.Sheet.Tag, null)),
                        ClippingRectangle = new Rectangle(item.Bounds.X, item.Bounds.Y,
                                                          item.Bounds.Width, item.Bounds.Height),
                        AppliedTransform = item.AppliedTransform,
                    };

                    JsonSerializer.Instance.Serialize(Path.Combine(context.BaseDirectory, context.Directory, Path.ChangeExtension(path, "asset")), imageRecipe);
                    */

                    List<UIImage> values = null;
                    if (imageBitmaps.TryGetValue(item.Source, out values))
                    {
                        foreach (var image in values)
                        {
                            image.Source.TextureURI = textureURI;
                            image.Source.ClippingRectangle = new Rectangle(item.Bounds.X, item.Bounds.Y,
                                                                           item.Bounds.Width, item.Bounds.Height);
                            image.Source.AppliedTransform = item.AppliedTransform;
                        }

                        /*
                        context.Store(Path.Combine(context.Directory, Path.ChangeExtension(path, null)), values[0].Source);

                        for (int i = 1; i < values.Count; i++)
                            values[i] = values[0];
                         */
                    }
                }
                #endregion
            }
        }

        private void ExportAllMasks(CookingContext context, ICollection<UIImage> images)
        {
            int maskNumber = 0;
            string maskOutputFormat = context.ExpandVariables(MaskOutput);

            var readMask = new ReadGameAsset();
            var maskRecipe = new GameAssetRecipe()
            {
                Cook = readMask,
                Author = GetType().FullName,
                Comment = "Automatically generated.",
            };

            var masks = new List<BitMask>(images.Count);
            foreach (var item in images)
            {
                if (item.Mask == null)
                    continue;

                string path = string.Format(maskOutputFormat, maskNumber++);

                readMask.Input = item.Mask;

                JsonSerializer.Instance.Serialize(Path.Combine(context.BaseDirectory, context.Directory, Path.ChangeExtension(path, "asset")), maskRecipe);
                context.Store(Path.Combine(context.Directory, Path.ChangeExtension(path, null)), item.Mask);
            }
        }
    }
}
