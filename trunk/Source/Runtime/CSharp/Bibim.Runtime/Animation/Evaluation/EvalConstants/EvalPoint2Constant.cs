using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'p', '2')]
    public sealed class EvalPoint2Constant : EvalConstantTemplate<Point2>
    {
        #region Constructors
        public EvalPoint2Constant()
        {
        }

        public EvalPoint2Constant(Point2 value)
            : base(value)
        {
        }
        #endregion
    }
}
