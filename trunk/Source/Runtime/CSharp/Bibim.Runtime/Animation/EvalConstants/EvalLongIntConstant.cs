using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'l', '_')]
    public sealed class EvalLongConstant : EvalConstantTemplate<long>
    {
        #region Constructors
        public EvalLongConstant()
        {
        }

        public EvalLongConstant(long value)
            : base(value)
        {
        }
        #endregion
    }
}
