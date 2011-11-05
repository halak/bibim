using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'p', '4')]
    public sealed class EvalPoint4Constant : EvalConstantTemplate<Point4>
    {
        #region Constructors
        public EvalPoint4Constant()
        {
        }

        public EvalPoint4Constant(Point4 value)
            : base(value)
        {
        }
        #endregion
    }
}
