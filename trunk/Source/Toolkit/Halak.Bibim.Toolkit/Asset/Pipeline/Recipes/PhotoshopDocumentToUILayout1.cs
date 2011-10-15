using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Text;
using System.Xml.Serialization;
using Microsoft.Xna.Framework;
using Halak.Bibim.Graphics;
using Halak.Bibim.UI;
using Halak.Bibim.UI.Frames;
using Halak.Bibim.UI.Visuals;
using Image = Halak.Bibim.Graphics.Image;
using Rectangle = Microsoft.Xna.Framework.Rectangle;
using GDIRectangle = System.Drawing.Rectangle;

namespace Halak.Bibim.Asset.Pipeline.Recipes
{
    public sealed class PhotoshopDocumentToUILayout1 : CookingNode<UILayout>
    {
        #region Fields
        private string textureOutput;
        private string imageOutput;
        #endregion

        #region Properties
        [XmlElement]
        public CookingNode<PhotoshopDocument> Input
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
        public PhotoshopDocumentToUILayout1()
            : this(null)
        {
        }

        public PhotoshopDocumentToUILayout1(CookingNode<PhotoshopDocument> input)
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

            PhotoshopDocument input = Input.Cook(context);

            Context ctx = new Context();

            Vector2 windowSize = Vector2.Zero;
            windowSize.X = (float)input.Width;
            windowSize.Y = (float)input.Height;
            UIWindow rootWindow = new UIWindow();
            rootWindow.Frame = new UIAlignedFrame(UIAlignedFrame.Alignment.Center, Vector2.Zero, windowSize);
            foreach (PhotoshopDocument.Layer item in input.Layers)
                AddChildTo(rootWindow, item, ctx);

            MergeAllSprites(context, ctx.Sprites);

            return new UILayout(rootWindow);
        }

        private static void AddChildTo(UIWindow window, PhotoshopDocument.Layer layer, Context context)
        {
            if (string.IsNullOrEmpty(layer.Name) ||
                layer.Name.StartsWith("#") == false)
                return;

            string name;
            string type;
            ParseLayerName(layer.Name, out name, out type);

            if (layer.IsGroup == false)
            {
                if (string.Compare(type, "UIMarkupLabel", true) == 0 ||
                    string.Compare(type, "MarkupLabel", true) == 0)
                {
                }
                else
                {
                    UISprite sprite = new UISprite();
                    sprite.Name = name;
                    window.AddChild(sprite);
                    Process(sprite, layer, context);
                }
            }
            else
            {
                if (string.Compare(type, "Button", true) == 0)
                {
                    UIButton button = new UIButton();
                    button.Name = name;
                    window.AddChild(button);
                    Process(button, layer, context);
                }
                else
                {
                    UIWindow childWindow = new UIWindow();
                    childWindow.Name = name;
                    window.AddChild(childWindow);
                    Process(childWindow, layer, context);
                }
            }
        }

        private static void Process(UIVisual visual, PhotoshopDocument.Layer layer, Context context)
        {
            System.Drawing.Rectangle parentBounds = System.Drawing.Rectangle.Empty;
            if (layer.Group != null)
                parentBounds = layer.Group.ComputeUnionRectangle();
            
            System.Drawing.Rectangle bounds = layer.ComputeUnionRectangle();
            bounds.X -= parentBounds.X;
            bounds.Y -= parentBounds.Y;

            visual.Frame = new UIAlignedFrame(UIAlignedFrame.Alignment.LeftTop,
                                              new Vector2((float)bounds.X, (float)bounds.Y),
                                              new Vector2((float)bounds.Width, (float)bounds.Height));
            visual.Opacity = (float)layer.Opacity / (float)byte.MaxValue;
            visual.Shown = layer.Visible;
        }

        private static void Process(UISprite sprite, PhotoshopDocument.Layer layer, Context context)
        {
            Process((UIVisual)sprite, layer, context);

            sprite.Image = new Image(string.Empty, Rectangle.Empty)
            {
                Tag = new ImageCookingTag(layer.Bitmap)
            };
            context.Sprites.Add(sprite);
        }

        private static void Process(UIButton button, PhotoshopDocument.Layer layer, Context context)
        {
            Process((UIVisual)button, layer, context);
        }

        private static void Process(UIWindow window, PhotoshopDocument.Layer layer, Context context)
        {
            Process((UIVisual)window, layer, context);

            for (int i = layer.SubLayers.Count - 1; i >= 0; i--)
                AddChildTo(window, layer.SubLayers[i], context);
        }

        private static void ParseLayerName(string layerName, out string name, out string type)
        {
            layerName = layerName.Trim();
            int index = layerName.LastIndexOf(':');
            if (index == -1)
            {
                name = layerName.Substring(1);
                type = string.Empty;
            }
            else
            {
                name = layerName.Substring(1, index - 1).Trim();
                type = layerName.Substring(index + 1).Trim();
            }
        }

        private void MergeAllSprites(CookingContext context, ICollection<UISprite> sprites)
        {
            var spriteBitmaps = new Dictionary<Bitmap, List<UISprite>>(sprites.Count);
            foreach (UISprite item in sprites)
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
                                                        true))
            {
                #region Texture File과 Asset을 저장합니다.
                var textureFileToStream = new FileToStream();
                var textureRecipe = new GameAssetRecipe()
                {
                    Cook = new BitmapToTexture2D(new ImportBitmap(textureFileToStream)),
                    Author = GetType().FullName,
                    Comment = "Automatically generated.", 
                };

                int textureNumber = 0;
                string textureOutputFormat = context.ExpandVariables(TextureOutput);
                foreach (Bitmap item in bitmapSheet.Sheets)
                {
                    Trace.Assert(item.Tag == null); // 밑에서 Tag를 직접 사용할 것이기 때문에 확인합니다.

                    string path = string.Format(textureOutputFormat, textureNumber++);

                    string textureFilePath = Path.ChangeExtension(path, "png");
                    item.Save(Path.Combine(context.BaseDirectory, context.Directory, textureFilePath), ImageFormat.Png);
                    item.Tag = textureFilePath;

                    textureFileToStream.Input1 = textureFilePath;

                    using (var fs = new FileStream(Path.Combine(context.BaseDirectory, context.Directory, Path.ChangeExtension(path, "asset")), FileMode.Create, FileAccess.Write))
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

        #region Context (Nested Class)
        private class Context
        {
            public List<UISprite> Sprites
            {
                get;
                private set;
            }

            public List<UILabel> Labels
            {
                get;
                private set;
            }

            public Context()
            {
                Sprites = new List<UISprite>();
                Labels = new List<UILabel>();
            }
        }
        #endregion
    }
}
