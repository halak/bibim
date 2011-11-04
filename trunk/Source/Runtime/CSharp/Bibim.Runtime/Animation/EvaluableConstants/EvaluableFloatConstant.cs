using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'f', '_')]
    public sealed class EvaluableFloatConstant : EvaluableConstantTemplate<float>
    {
        #region Constructors
        public EvaluableFloatConstant()
        {
        }

        public EvaluableFloatConstant(float value)
            : base(value)
        {
        }
        #endregion
    }
}
