using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'd', '_')]
    public sealed class EvaluableDoubleConstant : EvaluableConstantTemplate<double>
    {
        #region Constructors
        public EvaluableDoubleConstant()
        {
        }

        public EvaluableDoubleConstant(double value)
            : base(value)
        {
        }
        #endregion
    }
}
