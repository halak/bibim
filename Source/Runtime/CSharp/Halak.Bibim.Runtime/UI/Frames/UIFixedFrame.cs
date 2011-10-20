using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;

namespace Bibim.UI.Frames
{
    [ClassID('U', 'F', 'X', 'F')]
    public sealed class UIFixedFrame : UIFrame
    {
        #region Fields
        private RectangleF rectangle;
        #endregion

        #region Properties
        public RectangleF Rectangle
        {
            get { return rectangle; }
            set
            {
                rectangle = value;
            }
        }
        #endregion

        #region Constructors
        public UIFixedFrame()
        {
        }

        public UIFixedFrame(int x, int y, int width, int height)
            : this((float)x, (float)y, (float)width, (float)height)
        {
        }

        public UIFixedFrame(float x, float y, float width, float height)
        {
            rectangle = RectangleF.Empty;
            rectangle.X = x;
            rectangle.Y = y;
            rectangle.Width = width;
            rectangle.Height = height;
        }
        #endregion

        #region Methods
        #endregion
    }
}
