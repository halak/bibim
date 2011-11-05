using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'p', '2')]
    public sealed class EvalPoint2Variable : EvalVariableTemplate<Point2>
    {
        #region Constructors
        public EvalPoint2Variable()
        {
        }

        public EvalPoint2Variable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
