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
    public class PhotoshopDocumentToImageSet : CookingNode<ImageSet>
    {
        #region Properties
        public CookingNode<PhotoshopDocument> Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public PhotoshopDocumentToImageSet()
            : this(null)
        {
        }

        public PhotoshopDocumentToImageSet(CookingNode<PhotoshopDocument> input)
        {
            Input = input;
        }
        #endregion

        public override ImageSet Cook(CookingContext context)
        {
            PhotoshopDocument input = Input.Cook(context);

            Dictionary<string, Image> items = new Dictionary<string, Image>();
            foreach (PhotoshopDocument.Layer item in input.Layers)
                CollectImages(items, item);

            return new ImageSet(items);
        }

        private void CollectImages(Dictionary<string, Image> images, PhotoshopDocument.Layer layer)
        {
            if (layer.Name[0] == '@')
            {
                images.Add(layer.Name.Substring(1),
                           new Image(string.Empty, Rectangle.Empty)
                           {
                               Tag = new ImageCookingTag(layer.Bitmap)
                           });
            }

            foreach (PhotoshopDocument.Layer item in layer.SubLayers)
                CollectImages(images, item);
        }
    }
}
