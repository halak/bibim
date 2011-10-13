using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Halak.Bibim.Asset;

namespace Halak.Bibim.Graphics
{
    [ClassID('G', 'I', 'M', 'G')]
    public sealed class Image : GameAsset
    {
        #region Fields
        #endregion

        #region Properties
        public string TextureURI
        {
            get;
            set;
        }

        public Rectangle ClippingRectangle
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public Image()
        {
        }

        public Image(string textureURI, Rectangle clippingRectangle)
        {
            TextureURI = textureURI;
            ClippingRectangle = clippingRectangle;
        }
        #endregion

        #region Methods
        #endregion
    }
}
