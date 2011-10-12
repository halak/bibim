using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;

namespace Halak.Bibim.UI.Frames
{
    [ClassID('U', 'F', 'X', 'F')]
    public sealed class UIFixedFrame : UIFrame
    {
        #region Fields
        #endregion

        #region Properties
        public RectF Rectangle
        {
            get;
            set;
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
            Rectangle = RectF.Empty;
            Rectangle.X = x;
            Rectangle.Y = y;
            Rectangle.Width = width;
            Rectangle.Height = height;
        }
        #endregion

        #region Methods
        #endregion
    }
}
