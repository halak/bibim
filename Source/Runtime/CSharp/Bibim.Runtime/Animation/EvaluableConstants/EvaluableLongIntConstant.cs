using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'l', '_')]
    public sealed class EvaluableLongConstant : EvaluableConstantTemplate<long>
    {
        #region Constructors
        public EvaluableLongConstant()
        {
        }

        public EvaluableLongConstant(long value)
            : base(value)
        {
        }
        #endregion
    }
}
