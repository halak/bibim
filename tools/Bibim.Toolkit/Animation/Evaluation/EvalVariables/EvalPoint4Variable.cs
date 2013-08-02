using System;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'p', '4')]
    public sealed class EvalPoint4Variable : EvalVariableTemplate<Point4>
    {
        #region Constructors
        public EvalPoint4Variable()
        {
        }

        public EvalPoint4Variable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
