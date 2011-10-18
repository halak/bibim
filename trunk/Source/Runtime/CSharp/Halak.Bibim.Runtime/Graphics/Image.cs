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
        #region SimpleTransform (Nested Enum)
        public enum Transform
        {
            Identity,
            RotateCW90,
            RotateCW180,
            RotateCW270,
        }
        #endregion

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

        public Transform AppliedTransform
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
            : this(textureURI, clippingRectangle, Transform.Identity)
        {
        }

        public Image(string textureURI, Rectangle clippingRectangle, Transform appliedTransform)
        {
            TextureURI = textureURI;
            ClippingRectangle = clippingRectangle;
            AppliedTransform = appliedTransform;
        }
        #endregion

        #region Methods
        #endregion
    }
}
