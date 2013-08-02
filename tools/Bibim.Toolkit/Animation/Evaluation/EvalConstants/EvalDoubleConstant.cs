using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'd', '_')]
    public sealed class EvalDoubleConstant : EvalConstantTemplate<double>
    {
        #region Constructors
        public EvalDoubleConstant()
        {
        }

        public EvalDoubleConstant(double value)
            : base(value)
        {
        }
        #endregion
    }
}
