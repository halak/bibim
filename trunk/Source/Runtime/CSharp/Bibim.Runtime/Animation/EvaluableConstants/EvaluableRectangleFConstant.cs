using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'R', 'f')]
    public sealed class EvaluableRectangleFConstant : EvaluableConstantTemplate<RectangleF>
    {
        #region Constructors
        public EvaluableRectangleFConstant()
        {
        }

        public EvaluableRectangleFConstant(RectangleF value)
            : base(value)
        {
        }
        #endregion
    }
}
