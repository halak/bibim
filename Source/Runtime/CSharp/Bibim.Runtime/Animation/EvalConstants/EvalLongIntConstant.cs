using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'l', '_')]
    public sealed class EvalLongIntConstant : EvalConstantTemplate<long>
    {
        #region Constructors
        public EvalLongIntConstant()
        {
        }

        public EvalLongIntConstant(long value)
            : base(value)
        {
        }
        #endregion
    }
}
