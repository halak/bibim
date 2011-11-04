using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'p', '_')]
    public sealed class EvaluablePointVariable : EvaluableVariableTemplate<Point>
    {
        #region Constructors
        public EvaluablePointVariable()
        {
        }

        public EvaluablePointVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
