using System;
using System.Drawing;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'r', '_')]
    public sealed class EvalRectConstant : EvalConstantTemplate<Rectangle>
    {
        #region Constructors
        public EvalRectConstant()
        {
        }

        public EvalRectConstant(Rectangle value)
            : base(value)
        {
        }
        #endregion
    }
}
