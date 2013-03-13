using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using Microsoft.Xna.Framework;
using Bibim.Graphics;
using Bibim.UI;
using Bibim.UI.Effects;
using Bibim.UI.Events;
using Bibim.UI.Visuals;
using Image = Bibim.Graphics.Image;
using Rectangle = Microsoft.Xna.Framework.Rectangle;
using GDIGraphics = System.Drawing.Graphics;
using GDIColor = System.Drawing.Color;

namespace Bibim.Asset.Pipeline.Recipes
{
    public class PhotoshopDocumentToUILayout1 : CookingNode<UILayout>
    {
        #region Properties
        public CookingNode<PhotoshopDocument> Input
        {
            get;
            set;
        }

        public bool ForceShowAll
        {
            get;
            set;
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
        }
        #endregion

        public override UILayout Cook(CookingContext context)
        {
            PhotoshopDocument input = Input.Cook(context);
            
            Vector2 windowSize = Vector2.Zero;
            windowSize.X = (float)input.Width;
            windowSize.Y = (float)input.Height;
            UIWindow rootWindow = new UIWindow()
            {
                XMode = UIPositionMode.Undefined,
                YMode = UIPositionMode.Undefined,
                WidthMode = UISizeMode.Absolute,
                HeightMode = UISizeMode.Absolute,
                Width = windowSize.X,
                Height = windowSize.Y,
            };
            foreach (var item in input.Layers)
                AddChildTo(rootWindow, item, true);
            
            return new UILayout(rootWindow);
        }

        private void AddChildTo(UIWindow window, PhotoshopDocument.Layer layer, bool defaultPickable)
        {
            if (string.IsNullOrEmpty(layer.Name) ||
                layer.Name.StartsWith("#") == false)
                return;

            string name;
            string type;
            Dictionary<string, string> args;
            ParseLayerName(layer.Name, out name, out type, out args);

            if (layer.IsGroup == false)
            {
                if (string.Compare(type, "UIMarkupLabel", true) == 0 ||
                    string.Compare(type, "MarkupLabel", true) == 0 ||
                    string.Compare(type, "Label", true) == 0)
                {
                    UILabel label = new UILabel();
                    label.Name = name;
                    label.IsPickable = defaultPickable;
                    window.AddChild(label);
                    Process(label, layer);
                }
                else if (string.Compare(type, "9Patch", true) == 0 ||
                    string.Compare(type, "NinePatch", true) == 0 ||
                    string.Compare(type, "9P", true) == 0)
                {
                    UIWindow childWindow = new UIWindow();
                    childWindow.Name = name;
                    childWindow.IsPickable = defaultPickable;
                    window.AddChild(childWindow);
                    Process((UIPanel)childWindow, layer);

                    int leftBorder = int.Parse(args["0"] ?? "0");
                    int topBorder = int.Parse(args["1"] ?? "0");
                    int rightBorder = int.Parse(args["2"] ?? "0");
                    int bottomBorder = int.Parse(args["3"] ?? "0");

                    int horizontalBorder = leftBorder + rightBorder;
                    int verticalBorder = topBorder + bottomBorder;

                    int bw = layer.Bitmap.Width;
                    int bh = layer.Bitmap.Height;
                    Bitmap leftTopImage = ClipBitmap(layer.Bitmap, new Rectangle(0, 0, leftBorder, topBorder));
                    Bitmap rightTopImage = ClipBitmap(layer.Bitmap, new Rectangle(bw - rightBorder, 0, rightBorder, topBorder));
                    Bitmap leftBottomImage = ClipBitmap(layer.Bitmap, new Rectangle(0, bh - bottomBorder, leftBorder, bottomBorder));
                    Bitmap rightBottomImage = ClipBitmap(layer.Bitmap, new Rectangle(bw - rightBorder, bh - bottomBorder, rightBorder, bottomBorder));
                    Bitmap leftImage = ClipBitmap(layer.Bitmap, new Rectangle(0, topBorder, leftBorder, bh - verticalBorder));
                    Bitmap topImage = ClipBitmap(layer.Bitmap, new Rectangle(leftBorder, 0, bw - horizontalBorder, topBorder));
                    Bitmap rightImage = ClipBitmap(layer.Bitmap, new Rectangle(bw - rightBorder, topBorder, rightBorder, bh - verticalBorder));
                    Bitmap bottomImage = ClipBitmap(layer.Bitmap, new Rectangle(leftBorder, bh - bottomBorder, bw - horizontalBorder, bottomBorder));
                    Bitmap centerImage = ClipBitmap(layer.Bitmap, new Rectangle(leftBorder, topBorder, 16, 16));

                    var images = new List<UIImage>(9);
                    images.Add(CreateNinePatchPart(leftTopImage, UIAnchorPoint.LeftTop, new Vector2(0.0f, 0.0f), 0, 0, leftBorder, topBorder, UISizeMode.Absolute, UISizeMode.Absolute));
                    images.Add(CreateNinePatchPart(rightTopImage, UIAnchorPoint.RightTop, new Vector2(1.0f, 0.0f), 0, 0, rightBorder, topBorder, UISizeMode.Absolute, UISizeMode.Absolute));
                    images.Add(CreateNinePatchPart(leftBottomImage, UIAnchorPoint.LeftBottom, new Vector2(0.0f, 1.0f), 0, 0, leftBorder, bottomBorder, UISizeMode.Absolute, UISizeMode.Absolute));
                    images.Add(CreateNinePatchPart(rightBottomImage, UIAnchorPoint.RightBottom, new Vector2(1.0f, 1.0f), 0, 0, rightBorder, bottomBorder, UISizeMode.Absolute, UISizeMode.Absolute));

                    images.Add(CreateNinePatchPart(leftImage, UIAnchorPoint.LeftTop, new Vector2(0.0f, 0.0f), 0, topBorder, leftBorder, -verticalBorder, UISizeMode.Absolute, UISizeMode.Adjustive)); // left
                    images.Add(CreateNinePatchPart(topImage, UIAnchorPoint.LeftTop, new Vector2(0.0f, 0.0f), leftBorder, 0, -horizontalBorder, topBorder, UISizeMode.Adjustive, UISizeMode.Absolute)); // top
                    images.Add(CreateNinePatchPart(rightImage, UIAnchorPoint.RightTop, new Vector2(1.0f, 0.0f), 0, topBorder, rightBorder, -verticalBorder, UISizeMode.Absolute, UISizeMode.Adjustive)); // right
                    images.Add(CreateNinePatchPart(bottomImage, UIAnchorPoint.LeftBottom, new Vector2(0.0f, 1.0f), leftBorder, 0, -horizontalBorder, bottomBorder, UISizeMode.Adjustive, UISizeMode.Absolute)); // bototm

                    images.Add(CreateNinePatchPart(centerImage, UIAnchorPoint.LeftTop, new Vector2(0.0f, 0.0f), leftBorder, topBorder, -horizontalBorder, -verticalBorder, UISizeMode.Adjustive, UISizeMode.Adjustive));

                    foreach (var item in images)
                    {
                        if (item != null)
                            childWindow.AddChild(item);
                    }
                }
                else
                {
                    UIImage image = new UIImage();
                    image.Name = name;
                    image.IsPickable = defaultPickable;
                    window.AddChild(image);
                    Process(image, layer, string.Compare(type, "MaskImage", true) == 0 || string.Compare(type, "MaskSprite", true) == 0);
                }
            }
            else
            {
                if (string.Compare(type, "Button", true) == 0)
                {
                    UIButton button = new UIButton();
                    button.Name = name;
                    button.IsPickable = true;
                    window.AddChild(button);
                    Process(button, layer);
                }
                else if (string.Compare(type, "CheckBox", true) == 0)
                {
                    UICheckBox button = new UICheckBox();
                    button.Name = name;
                    button.IsPickable = true;
                    window.AddChild(button);
                    Process(button, layer);
                }
                else if (string.Compare(type, "Radio", true) == 0)
                {
                    UIRadioButton button = new UIRadioButton();
                    button.Name = name;
                    button.IsPickable = true;
                    window.AddChild(button);
                    Process(button, layer);
                }
                else
                {
                    bool hasNormal = layer.FindSubLayer("#Normal", false) != null;
                    bool hasPushed = layer.FindSubLayer("#Pushed", false) != null;
                    bool hasHovering = layer.FindSubLayer("#Hovering", false) != null;
                    bool hasCheckedNormal = layer.FindSubLayer("#CheckedNormal", false) != null;
                    bool hasCheckedPushed = layer.FindSubLayer("#CheckedPushed", false) != null;
                    bool hasCheckedHovering = layer.FindSubLayer("#CheckedHovering", false) != null;
                    if (hasNormal && hasPushed && !hasCheckedNormal && !hasCheckedPushed)
                    {
                        UIButton button = new UIButton();
                        button.Name = name;
                        button.IsPickable = true;
                        window.AddChild(button);
                        Process(button, layer);
                    }
                    else if (hasNormal && hasCheckedNormal)
                    {
                        UICheckBox button = new UICheckBox();
                        button.Name = name;
                        button.IsPickable = true;
                        window.AddChild(button);
                        Process(button, layer);
                    }
                    else
                    {
                        UIWindow childWindow = new UIWindow();
                        childWindow.Name = name;
                        childWindow.IsPickable = defaultPickable;
                        window.AddChild(childWindow);
                        Process(childWindow, layer);
                    }
                }
            }
        }

        private void Process(UIVisual visual, PhotoshopDocument.Layer layer)
        {
            System.Drawing.Rectangle parentBounds = System.Drawing.Rectangle.Empty;
            if (layer.Group != null)
                parentBounds = layer.Group.ComputeUnionRectangle();
            
            System.Drawing.Rectangle bounds = layer.ComputeUnionRectangle();
            bounds.X -= parentBounds.X;
            bounds.Y -= parentBounds.Y;

            visual.SetAbsoluteBounds(bounds.X, bounds.Y, bounds.Width, bounds.Height);
            visual.Opacity = (float)layer.Opacity / (float)byte.MaxValue;
            if (ForceShowAll)
                visual.Visibility = UIVisibility.Visible;
            else
                visual.Visibility = layer.Visible ? UIVisibility.Visible : UIVisibility.Invisible;

            BlendMode blendMode = ConvertToBlendMode(layer.BlendMode);
            if (blendMode != BlendMode.Normal)
            {
                visual.EffectMap = new UIEffectMap();
                visual.EffectMap.Insert(new UIBlendingEffect(blendMode));
            }
        }

        private void Process(UIImage image, PhotoshopDocument.Layer layer, bool importMask)
        {
            Process((UIVisual)image, layer);

            Bitmap bitmap = layer.Bitmap;

            if (image.EffectMap != null)
            {
                UIBlendingEffect effect = (UIBlendingEffect)image.EffectMap.GetPixelEffect(UIBlendingEffect.ClassIndex);
                switch (effect.Mode)
                {
                    case BlendMode.Additive:
                    case BlendMode.Lighten:
                    case BlendMode.Screen:
                        bitmap = ConvertToBlendableBitmap(bitmap, GDIColor.Black);
                        break;
                    case BlendMode.Darken:
                    case BlendMode.Multiply:
                        bitmap = ConvertToBlendableBitmap(bitmap, GDIColor.White);
                        break;
                }
            }

            image.Source = new Image(string.Empty, Rectangle.Empty)
            {
                Tag = new ImageCookingTag(bitmap)
            };

            if (importMask)
                image.Mask = GenerateBitMask(bitmap);
        }

        private void Process(UILabel label, PhotoshopDocument.Layer layer)
        {
            Process((UIVisual)label, layer);
        }

        private void Process(UIButton button, PhotoshopDocument.Layer layer)
        {
            Process((UIVisual)button, layer);

            PhotoshopDocument.Layer normal = layer.FindSubLayer("#Normal", true);
            PhotoshopDocument.Layer pushed = layer.FindSubLayer("#Pushed", true);
            PhotoshopDocument.Layer hovering = layer.FindSubLayer("#Focusing", true);

            if (hovering == null)
                hovering = layer.FindSubLayer("#Hovering", true);
            if (hovering == null)
                hovering = normal;
            if (pushed == null)
                pushed = hovering;

            if (normal != null)
            {
                var window = new UIWindow();
                button.Normal = window;
                AddChildTo(window, normal, false);
            }
            if (pushed != null)
            {
                var window = new UIWindow();
                button.Pushed = window;
                AddChildTo(window, pushed, false);
            }
            if (hovering != null)
            {
                var window = new UIWindow();
                button.Hovering = window;
                AddChildTo(window, hovering, false);
            }
        }

        private void Process(UICheckBox button, PhotoshopDocument.Layer layer)
        {
            Process((UIButton)button, layer);

            PhotoshopDocument.Layer normal = layer.FindSubLayer("#CheckedNormal", true);
            PhotoshopDocument.Layer pushed = layer.FindSubLayer("#CheckedPushed", true);
            PhotoshopDocument.Layer hovering = layer.FindSubLayer("#CheckedFocusing", true);

            if (hovering == null)
                hovering = layer.FindSubLayer("#CheckedHovering", true);
            if (hovering == null)
                hovering = normal;
            if (pushed == null)
                pushed = hovering;

            if (normal != null)
            {
                var window = new UIWindow();
                button.CheckedNormal = window;
                button.CheckedNormal.Visibility = UIVisibility.Invisible;
                AddChildTo(window, normal, false);
            }
            if (pushed != null)
            {
                var window = new UIWindow();
                button.CheckedPushed = window;
                button.CheckedPushed.Visibility = UIVisibility.Invisible;
                AddChildTo(window, pushed, false);
            }
            if (hovering != null)
            {
                var window = new UIWindow();
                button.CheckedHovering = window;
                button.CheckedHovering.Visibility = UIVisibility.Invisible;
                AddChildTo(window, hovering, false);
            }
        }

        private void Process(UIRadioButton button, PhotoshopDocument.Layer layer)
        {
            Process((UICheckBox)button, layer);
        }

        private void Process(UIWindow window, PhotoshopDocument.Layer layer)
        {
            Process((UIVisual)window, layer);

            for (int i = layer.SubLayers.Count - 1; i >= 0; i--)
                AddChildTo(window, layer.SubLayers[i], true);
        }

        private UIImage CreateNinePatchPart(Bitmap bitmap, UIAnchorPoint anchor, Vector2 origin, int x, int y, int width, int height, UISizeMode widthMode, UISizeMode heightMode)
        {
            if (bitmap == null)
                return null;

            if (IsSingleColor(bitmap))
            {
                var solidColor = bitmap.GetPixel(0, 0);
                bitmap = new Bitmap(1, 1);
                bitmap.SetPixel(0, 0, solidColor);
            }

            UIImage image = new UIImage();
            image.AnchorPoint = anchor;
            image.Origin = origin;
            image.X = (float)x;
            image.Y = (float)y;
            image.XMode = UIPositionMode.Absolute;
            image.YMode = UIPositionMode.Absolute;
            image.Width = (float)width;
            image.Height = (float)height;
            image.WidthMode = widthMode;
            image.HeightMode = heightMode;
            image.Source = new Image(string.Empty, Rectangle.Empty)
            {
                Tag = new ImageCookingTag(bitmap)
            };

            return image;
        }

        private static void ParseLayerName(string layerName, out string name, out string type, out Dictionary<string, string> args)
        {
            layerName = layerName.Trim();
            int index = layerName.LastIndexOf(':');
            if (index == -1)
            {
                name = layerName.Substring(1);
                type = string.Empty;
                args = new Dictionary<string, string>();
            }
            else
            {
                name = layerName.Substring(1, index - 1).Trim();
                type = layerName.Substring(index + 1).Trim();
                args = new Dictionary<string,string>();

                int argsStart = type.IndexOf('(');
                if (argsStart != -1)
                {
                    argsStart += 1;
                    int argsEnd = type.LastIndexOf(')');
                    string argsText = null;
                    if (argsEnd != -1)
                        argsText = type.Substring(argsStart, argsEnd - argsStart);
                    else
                        argsText = type.Substring(argsStart);

                    string[] argsArray = argsText.Split(',');
                    for (int i = 0; i < argsArray.Length; i++)
                    {
                        string value = null;
                        if (argsArray[i].Equals('_') == false)
                            value = argsArray[i];

                        args[i.ToString()] = value;
                    }

                    type = type.Substring(0, argsStart - 1).Trim();
                }
            }
        }

        private static BlendMode ConvertToBlendMode(PhotoshopDocument.BlendMode source)
        {
            switch (source)
            {
                case PhotoshopDocument.BlendMode.Darken:
                    return BlendMode.Darken;
                case PhotoshopDocument.BlendMode.Multiply:
                    return BlendMode.Multiply;
                case PhotoshopDocument.BlendMode.ColorBurn:
                    return BlendMode.Darken;
                case PhotoshopDocument.BlendMode.LinearBurn:
                    return BlendMode.Darken;
                case PhotoshopDocument.BlendMode.Lighten:
                    return BlendMode.Lighten;
                case PhotoshopDocument.BlendMode.Screen:
                    return BlendMode.Screen;
                case PhotoshopDocument.BlendMode.ColorDodge:
                    return BlendMode.LinearDodge;
                case PhotoshopDocument.BlendMode.LinearDodge:
                    return BlendMode.LinearDodge;
                case PhotoshopDocument.BlendMode.Overlay:
                    return BlendMode.Multiply;
                case PhotoshopDocument.BlendMode.SoftLight:
                    return BlendMode.Multiply;
                case PhotoshopDocument.BlendMode.HardLight:
                    return BlendMode.Lighten;
                case PhotoshopDocument.BlendMode.VividLight:
                    return BlendMode.Lighten;
                case PhotoshopDocument.BlendMode.LinearLight:
                    return BlendMode.Lighten;
                case PhotoshopDocument.BlendMode.PinLight:
                    return BlendMode.Lighten;
                default:
                    return BlendMode.Normal;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="bitmap"></param>
        /// <param name="backColor"></param>
        /// <returns></returns>
        private static Bitmap ConvertToBlendableBitmap(Bitmap bitmap, GDIColor backColor)
        {
            Bitmap result = new Bitmap(bitmap.Width, bitmap.Height);

            double backColorR = ((double)backColor.R) / 255.0;
            double backColorG = ((double)backColor.G) / 255.0;
            double backColorB = ((double)backColor.B) / 255.0;

            int w = bitmap.Width;
            int h = bitmap.Height;
            for (int y = 0; y < h; y++)
            {
                for (int x = 0; x < w; x++)
                {
                    GDIColor c = bitmap.GetPixel(x, y);
                    double alpha = ((double)c.A) / 255.0;
                    double invAlpha = 1.0 - alpha;
                    double r = Math.Min(((double)c.R) / 255.0 * alpha + backColorR * invAlpha, 1.0);
                    double g = Math.Min(((double)c.G) / 255.0 * alpha + backColorG * invAlpha, 1.0);
                    double b = Math.Min(((double)c.B) / 255.0 * alpha + backColorB * invAlpha, 1.0);
                    result.SetPixel(x, y,
                                    GDIColor.FromArgb(255,
                                                      (int)(r * 255.0),
                                                      (int)(g * 255.0),
                                                      (int)(b * 255.0)));
                }
            }

            return result;
        }

        public static BitMask GenerateBitMask(Bitmap bitmap)
        {
            int width = bitmap.Width;
            int height = bitmap.Height;
            int pitch = 0;
            if (width % 8 == 0)
                pitch = (int)(width / 8);
            else
                pitch = (int)(width / 8) + 1;
            byte[] buffer = new byte[pitch * height];

            int baseIndex = 0;
            for (int y = 0; y < height; y++, baseIndex += pitch)
            {
                for (int x = 0; x < width; x++)
                {
                    GDIColor c = bitmap.GetPixel(x, y);
                    int index = baseIndex + (int)(x / 8);
                    int mask = (0x00000080) >> (x % 8);
                    if (c.A > 0)
                        buffer[index] |= (byte)mask;
                    else
                    {
                        mask = ~mask;
                        buffer[index] &= (byte)mask;
                    }
                }
            }

            return new BitMask(width, height, pitch, buffer);
        }

        public static Bitmap ClipBitmap(Bitmap source, Rectangle rectangle)
        {
            if (rectangle.Width == 0 || rectangle.Height == 0)
                return null;

            var result = new Bitmap(rectangle.Width, rectangle.Height);
            using (var g = GDIGraphics.FromImage(result))
            {
                g.DrawImage(source,
                            new System.Drawing.Rectangle(0, 0, result.Width, result.Height),
                            new System.Drawing.Rectangle(rectangle.X, rectangle.Y, rectangle.Width, rectangle.Height),
                            GraphicsUnit.Pixel);
            }

            return result;
        }

        private static bool IsSingleColor(Bitmap source)
        {
            int w = source.Width;
            int h = source.Height;
            var firstColor = source.GetPixel(0, 0);
            for (int y = 0; y < h; y++)
            {
                for (int x = 0; x < w; x++)
                {
                    if (source.GetPixel(x, y) != firstColor)
                        return false;
                }
            }

            return true;
        }
    }
}
