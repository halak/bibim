﻿using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Serialization;
using Microsoft.Xna.Framework;
using Halak.Bibim.Graphics;
using Halak.Bibim.UI;
using Halak.Bibim.UI.Frames;
using Halak.Bibim.UI.Visuals;

namespace Halak.Bibim.Asset.Pipeline.Recipes
{
    public sealed class PhotoshopDocumentToUILayout1 : CookingNode<UILayout>
    {
        #region Properties
        [XmlElement]
        public CookingNode<PhotoshopDocument> Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public PhotoshopDocumentToUILayout1()
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
            UIWindow rootWindow = new UIWindow();
            rootWindow.Frame = new UIAlignedFrame(UIAlignedFrame.Alignment.Center, Vector2.Zero, windowSize);
            foreach (PhotoshopDocument.Layer item in input.Layers)
                AddChildTo(rootWindow, item);

            return new UILayout(rootWindow);
        }

        private static void AddChildTo(UIWindow window, PhotoshopDocument.Layer layer)
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
                    UIWindow childWindow = new UIWindow();
                    childWindow.Name = name;
                    window.AddChild(childWindow);
                    Process(childWindow, layer);
                }
            }
        }

        private static void Process(UIVisual visual, PhotoshopDocument.Layer layer)
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

        private static void Process(UISprite sprite, PhotoshopDocument.Layer layer)
        {
            Process((UIVisual)sprite, layer);

            sprite.Image = new Image(string.Empty, Rectangle.Empty);
        }

        private static void Process(UIButton button, PhotoshopDocument.Layer layer)
        {
            Process((UIVisual)button, layer);
        }

        private static void Process(UIWindow window, PhotoshopDocument.Layer layer)
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
    }
}
