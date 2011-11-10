using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'R', 'f')]
    public sealed class EvalRectFConstant : EvalConstantTemplate<RectangleF>
    {
        #region Constructors
        public EvalRectFConstant()
        {
        }

        public EvalRectFConstant(RectangleF value)
            : base(value)
        {
        }
        #endregion
    }
}
