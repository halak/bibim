using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;

namespace Halak.Bibim.UI.Frames
{
    [ClassID('U', 'A', 'L', 'F')]
    public sealed class UIAlignedFrame : UIFrame
    {
        #region Alignment (Nested Enum)
        public enum Alignment
        {
            LeftTop,
            LeftBottom,
            LeftMiddle,
            RightTop,
            RightBottom,
            RightMiddle,
            CenterTop,
            CenterBottom,
            Center,
        };
        #endregion

        #region Fields
        private Alignment align;
        private Vector2 offset;
        private Vector2 size;
        private bool boundsChanged;
        #endregion

        #region Properties
        public Alignment Align
        {
            get { return align; }
            set
            {
                if (align != value)
                {
                    align = value;
                    boundsChanged = true;
                }
            }
        }

        public Vector2 Offset
        {
            get { return offset; }
            set
            {
                if (offset != value)
                {
                    offset = value;
                    boundsChanged = true;
                }
            }
        }

        public Vector2 Size
        {
            get { return size; }
            set
            {
                if (size != value)
                {
                    size = value;
                    boundsChanged = true;
                }
            }
        }
        #endregion

        #region Constructors
        public UIAlignedFrame()
        {
            align = Alignment.LeftTop;
            offset = Vector2.Zero;
            size = Vector2.Zero;
            boundsChanged = true;
        }

        public UIAlignedFrame(Alignment align, Vector2 offset, Vector2 size)
        {
            this.align = align;
            this.offset = offset;
            this.size = size;
            boundsChanged = true;
        }
        #endregion

        #region Methods
        #endregion
    }
}
