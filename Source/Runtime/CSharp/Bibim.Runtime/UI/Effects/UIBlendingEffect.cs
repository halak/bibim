using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Graphics;

namespace Bibim.UI.Effects
{
    [ClassID('U', 'B', 'L', 'F')]
    public class UIBlendingEffect : UIPixelEffect
    {
        public const int ClassIndex = 1;

        #region Properties
        public BlendMode Mode
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public UIBlendingEffect()
            : this(BlendMode.Normal)
        {
        }

        public UIBlendingEffect(BlendMode mode)
            : base(ClassIndex, false, false)
        {
            Mode = mode;
        }
        #endregion
    }
}
