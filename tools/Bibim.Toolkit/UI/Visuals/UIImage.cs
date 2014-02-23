using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Bibim.Graphics;

namespace Bibim.UI.Visuals
{
    [ClassID('U', 'I', 'M', 'G')]
    public class UIImage : UIVisual
    {
        #region Fields
        #endregion

        #region Properties
        public Image Source
        {
            get;
            set;
        }

        public bool HorizontalFlip
        {
            get;
            set;
        }

        public bool VerticalFlip
        {
            get;
            set;
        }

        public BitMask Mask
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public UIImage()
        {
            Width = 1.0f;
            Height = 1.0f;
            WidthMode = UISizeMode.Content;
            HeightMode = UISizeMode.Content;
        }
        #endregion

        #region Methods
        #endregion
    }
}
