using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'b', '_')]
    public sealed class EvalBoolConstant : EvalConstantTemplate<bool>
    {
        #region Constructors
        public EvalBoolConstant()
        {
        }

        public EvalBoolConstant(bool value)
            : base(value)
        {
        }
        #endregion
    }
}
