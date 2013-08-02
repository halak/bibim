using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'f', '_')]
    public sealed class EvalFloatConstant : EvalConstantTemplate<float>
    {
        #region Constructors
        public EvalFloatConstant()
        {
        }

        public EvalFloatConstant(float value)
            : base(value)
        {
        }
        #endregion
    }
}
