using System;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'p', '3')]
    public sealed class EvalPoint3Constant : EvalConstantTemplate<Point3>
    {
        #region Constructors
        public EvalPoint3Constant()
        {
        }

        public EvalPoint3Constant(Point3 value)
            : base(value)
        {
        }
        #endregion
    }
}
