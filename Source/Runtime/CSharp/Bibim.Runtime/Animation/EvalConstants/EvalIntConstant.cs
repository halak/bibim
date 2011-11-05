using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'i', '_')]
    public sealed class EvalIntConstant : EvalConstantTemplate<int>
    {
        #region Constructors
        public EvalIntConstant()
        {
        }

        public EvalIntConstant(int value)
            : base(value)
        {
        }
        #endregion
    }
}
