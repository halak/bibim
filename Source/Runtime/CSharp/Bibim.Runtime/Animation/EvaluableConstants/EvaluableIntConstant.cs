using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'i', '_')]
    public sealed class EvaluableIntConstant : EvaluableConstantTemplate<int>
    {
        #region Constructors
        public EvaluableIntConstant()
        {
        }

        public EvaluableIntConstant(int value)
            : base(value)
        {
        }
        #endregion
    }
}
