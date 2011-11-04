using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using Bibim.Graphics;
using Bibim.UI;
using Bibim.UI.Frames;
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
        #endregion

        #region Properties
        [XmlElement]
        public CookingNode<UILayout> Input
        {
            get;
            set;
        }

        [XmlElement]
        public Size BitmapSheetSize
        {
            get;
            set;
        }

        [XmlElement]
        public Size BitmapSheetClusterSize
        {
            get;
            set;
        }

        [XmlAttribute]
        public string TextureOutput
        {
            get { return textureOutput; }
            set
            {
                textureOutput = value ?? string.Empty;
            }
        }

        [XmlAttribute]
        public string ImageOutput
        {
            get { return imageOutput; }
            set
            {
                imageOutput = value ?? string.Empty;
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

            List<UISprite> sprites = new List<UISprite>();
            List<UILabel> labels = new List<UILabel>();
            CollectObjects(input.Root, sprites, labels);

            OptimizeAllSprites(context, sprites);
            MergeAllSprites(context, sprites);

            return input;
        }

        private static void CollectObjects(UIVisual visual, List<UISprite> sprites, List<UILabel> labels)
        {
            if (visual is UISprite)
                sprites.Add((UISprite)visual);
            else if (visual is UILabel)
                labels.Add((UILabel)visual);
            else if (visual is UIPanel)
            {
                foreach (UIVisual item in ((UIPanel)visual).Children)
                    CollectObjects(item, sprites, labels);
            }
        }

        private void OptimizeAllSprites(CookingContext context, ICollection<UISprite> sprites)
        {
            var uniqueImages = new List<Image>();
            foreach (var item in sprites)
            {
                bool found = false;
                foreach (var image in uniqueImages)
                {
                    if (EqualsImage(item.Image, image))
                    {
                        item.Image = image;
                        found = true;
                        break;
                    }
                }

                if (found == false)
                    uniqueImages.Add(item.Image);
            }
        }

        private static bool EqualsImage(Image a, Image b)
        {
            if (a == null || b == null)
                return false;

            var aTag = a.Tag as ImageCookingTag;
            var bTag = b.Tag as ImageCookingTag;

            if (aTag != null && bTag != null)
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

        private void MergeAllSprites(CookingContext context, ICollection<UISprite> sprites)
        {
            var spriteBitmaps = new Dictionary<Bitmap, List<UISprite>>(sprites.Count);
            foreach (var item in sprites)
            {
                var tag = item.Image.Tag as ImageCookingTag;
                if (tag != null)
                {
                    List<UISprite> values = null;
                    if (spriteBitmaps.TryGetValue(tag.Bitmap, out values))
                        values.Add(item);
                    else
                    {
                        values = new List<UISprite>() { item };
                        spriteBitmaps.Add(tag.Bitmap, values);
                    }
                }
            }

            using (var bitmapSheet = BitmapSheet.Create(spriteBitmaps.Keys,
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

                    using (var fs = new FileStream(Path.ChangeExtension(fullPath, "asset"), FileMode.Create, FileAccess.Write))
                        GameAssetRecipe.Serialize(fs, textureRecipe);
                }
                #endregion

                #region Image Asset을 저장합니다.
                var readImage = new ReadImage();
                var imageRecipe = new GameAssetRecipe()
                {
                    Cook = readImage,
                    Author = GetType().FullName,
                    Comment = "Automatically generated.",
                };

                int imageNumber = 0;
                string imageOutputFormat = context.ExpandVariables(ImageOutput);
                foreach (BitmapSheet.Element item in bitmapSheet.Elements)
                {
                    string path = string.Format(imageOutputFormat, imageNumber++);

                    readImage.TextureURI = Path.Combine(context.Directory, Path.ChangeExtension((string)item.Sheet.Tag, null));
                    readImage.ClippingRectangle = new Rectangle(item.Bounds.X, item.Bounds.Y,
                                                                item.Bounds.Width, item.Bounds.Height);
                    readImage.AppliedTransform = item.AppliedTransform;

                    using (var fs = new FileStream(Path.Combine(context.BaseDirectory, context.Directory, Path.ChangeExtension(path, "asset")), FileMode.Create, FileAccess.Write))
                        GameAssetRecipe.Serialize(fs, imageRecipe);

                    List<UISprite> values = null;
                    if (spriteBitmaps.TryGetValue(item.Source, out values))
                    {
                        context.Store(Path.Combine(context.Directory, Path.ChangeExtension(path, null)), values[0].Image);

                        for (int i = 1; i < values.Count; i++)
                            values[i] = values[0];
                    }
                }
                #endregion
            }
        }
    }
}
