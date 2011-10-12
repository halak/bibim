using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;

namespace Halak.Bibim.UI
{
    [ClassID('U', 'I', 'M', 'G')]
    public sealed class UIImage : UIElement
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
        public UIImage()
        {
        }

        public UIImage(string textureURI, Rectangle clippingRectangle)
        {
            TextureURI = textureURI;
            ClippingRectangle = clippingRectangle;
        }
        #endregion

        #region Methods
        #endregion
    }
}
