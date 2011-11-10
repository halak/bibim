using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'p', '3')]
    public sealed class EvalPoint3Variable : EvalVariableTemplate<Point3>
    {
        #region Constructors
        public EvalPoint3Variable()
        {
        }

        public EvalPoint3Variable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
