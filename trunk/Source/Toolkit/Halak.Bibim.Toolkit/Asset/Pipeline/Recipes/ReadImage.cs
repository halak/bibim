using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using Halak.Bibim.Graphics;
using Microsoft.Xna.Framework;

namespace Halak.Bibim.Asset.Pipeline.Recipes
{
    public sealed class ReadImage : CookingNode<Image>
    {
        #region Properties
        [XmlAttribute]
        public string TextureURI
        {
            get;
            set;
        }

        [XmlElement]
        public Rectangle ClippingRectangle
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public ReadImage()
            : this(string.Empty, Rectangle.Empty)
        {
        }

        public ReadImage(string textureURI, Rectangle clippingRectangle)
        {
        }
        #endregion

        #region Method
        public override Image Cook(CookingContext context)
        {
            return new Image(TextureURI, ClippingRectangle);
        }
        #endregion
    }
}
