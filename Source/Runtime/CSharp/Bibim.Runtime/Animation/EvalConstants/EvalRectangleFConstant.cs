using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'R', 'f')]
    public sealed class EvalRectangleFConstant : EvalConstantTemplate<RectangleF>
    {
        #region Constructors
        public EvalRectangleFConstant()
        {
        }

        public EvalRectangleFConstant(RectangleF value)
            : base(value)
        {
        }
        #endregion
    }
}
