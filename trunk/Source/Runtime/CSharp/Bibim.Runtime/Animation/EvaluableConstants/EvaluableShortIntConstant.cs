using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 's', '_')]
    public sealed class EvaluableShortIntConstant : EvaluableConstantTemplate<short>
    {
        #region Constructors
        public EvaluableShortIntConstant()
        {
        }

        public EvaluableShortIntConstant(short value)
            : base(value)
        {
        }
        #endregion
    }
}
