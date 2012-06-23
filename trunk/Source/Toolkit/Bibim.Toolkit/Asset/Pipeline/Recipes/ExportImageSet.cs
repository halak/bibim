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
    public sealed class ExportImageSet : CookingNode<ImageSet>
    {
        #region Fields
        private string textureOutput;
        #endregion

        #region Properties
        public CookingNode<ImageSet> Input
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
        public ExportImageSet()
            : this(null)
        {
        }

        public ExportImageSet(CookingNode<ImageSet> input)
        {
            Input = input;
            BitmapSheetSize = new Size(1024, 1024);
            BitmapSheetClusterSize = new Size(16, 16);
            textureOutput = "$(AssetName)_TEX{0}";
        }
        #endregion

        public override ImageSet Cook(CookingContext context)
        {
            if (BitmapSheetSize.IsEmpty)
                throw new InvalidOperationException("BitmapSheetSize is empty.");
            if (string.IsNullOrEmpty(TextureOutput))
                throw new InvalidOperationException("TextureOutput is null.");
            if (TextureOutput.Contains("{0}") == false)
                throw new InvalidOperationException("TextureOutput not exists {0}.");

            ImageSet input = Input.Cook(context);

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
                                                        BitmapSheetSize.Width, BitmapSheetSize.Height,
                                                        BitmapSheetClusterSize.Width, BitmapSheetClusterSize.Height,
                                                        BitmapSheet.Options.PowerOfTwoSize | BitmapSheet.Options.RotatableMerging))
            {
                #region Texture File과 Asset을 저장합니다.
                var textureFileToStream = new FileToStream();
                var textureRecipe = new GameAssetRecipe()
                {
                    Cook = new BitmapToTexture2D(new ImportBitmap(textureFileToStream)),
                    Author = GetType().Name,
                    Comment = "Automatically generated.",
                };

                string absoluteDirectory = Path.Combine(context.BaseDirectory, context.Directory);
                if (Directory.Exists(absoluteDirectory) == false)
                    Directory.CreateDirectory(absoluteDirectory);

                int textureNumber = 0;
                string textureOutputFormat = context.ExpandVariables(textureOutput);
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

                #region Image Asset을 저장합니다.
                foreach (BitmapSheet.Element item in bitmapSheet.Elements)
                {
                    string textureURI = Path.Combine(context.Directory, Path.ChangeExtension((string)item.Sheet.Tag, null));
                    var clippingRectangle = new Rectangle(item.Bounds.X, item.Bounds.Y,
                                                          item.Bounds.Width, item.Bounds.Height);
                    var appliedTransform = item.AppliedTransform;

                    List<Image> values = null;
                    if (imageBitmaps.TryGetValue(item.Source, out values))
                    {
                        foreach (Image image in values)
                        {
                            image.TextureURI = textureURI;
                            image.ClippingRectangle = clippingRectangle;
                            image.AppliedTransform = appliedTransform;
                        }
                    }
                }
                #endregion
            }

            return input;
        }
    }
}
