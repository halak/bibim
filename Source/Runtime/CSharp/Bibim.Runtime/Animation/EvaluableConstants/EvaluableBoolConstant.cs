using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'b', '_')]
    public sealed class EvaluableBoolConstant : EvaluableConstantTemplate<bool>
    {
        #region Constructors
        public EvaluableBoolConstant()
        {
        }

        public EvaluableBoolConstant(bool value)
            : base(value)
        {
        }
        #endregion
    }
}
