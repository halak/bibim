using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 's', '_')]
    public sealed class EvalShortIntConstant : EvalConstantTemplate<short>
    {
        #region Constructors
        public EvalShortIntConstant()
        {
        }

        public EvalShortIntConstant(short value)
            : base(value)
        {
        }
        #endregion
    }
}
