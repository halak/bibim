using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Text;
using Microsoft.Xna.Framework;
using Bibim.Graphics;
using Bibim.UI;
using Bibim.UI.Effects;
using Bibim.UI.Events;
using Bibim.UI.Visuals;
using Image = Bibim.Graphics.Image;
using Rectangle = Microsoft.Xna.Framework.Rectangle;
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
            foreach (PhotoshopDocument.Layer item in input.Layers)
                AddChildTo(rootWindow, item);
            
            return new UILayout(rootWindow);
        }

        private void AddChildTo(UIWindow window, PhotoshopDocument.Layer layer)
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
                    UILabel label = new UILabel();
                    label.Name = name;
                    window.AddChild(label);
                    Process(label, layer);
                }
                else
                {
                    UISprite sprite = new UISprite();
                    sprite.Name = name;
                    window.AddChild(sprite);
                    Process(sprite, layer);
                }
            }
            else
            {
                if (string.Compare(type, "Button", true) == 0)
                {
                    UIButton button = new UIButton();
                    button.Name = name;
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
                        window.AddChild(button);
                        Process(button, layer);
                    }
                    else if (hasNormal && hasPushed && hasCheckedNormal && hasCheckedPushed)
                    {
                        UICheckBox button = new UICheckBox();
                        button.Name = name;
                        window.AddChild(button);
                        Process(button, layer);
                    }
                    else
                    {
                        UIWindow childWindow = new UIWindow();
                        childWindow.Name = name;
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

        private void Process(UISprite sprite, PhotoshopDocument.Layer layer)
        {
            Process((UIVisual)sprite, layer);

            Bitmap bitmap = layer.Bitmap;

            if (sprite.EffectMap != null)
            {
                UIBlendingEffect effect = (UIBlendingEffect)sprite.EffectMap.GetPixelEffect(UIBlendingEffect.ClassIndex);
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

            sprite.Image = new Image(string.Empty, Rectangle.Empty)
            {
                Tag = new ImageCookingTag(bitmap)
            };
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
                AddChildTo(window, normal);
            }
            if (pushed != null)
            {
                var window = new UIWindow();
                button.Pushed = window;
                AddChildTo(window, pushed);
            }
            if (hovering != null)
            {
                var window = new UIWindow();
                button.Hovering = window;
                AddChildTo(window, hovering);
            }
        }

        private void Process(UIWindow window, PhotoshopDocument.Layer layer)
        {
            Process((UIVisual)window, layer);

            for (int i = layer.SubLayers.Count - 1; i >= 0; i--)
                AddChildTo(window, layer.SubLayers[i]);
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
    }
}
