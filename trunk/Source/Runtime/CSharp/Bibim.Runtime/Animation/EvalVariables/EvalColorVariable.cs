using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'c', '_')]
    public sealed class EvalColorVariable : EvalVariableTemplate<Color>
    {
        #region Constructors
        public EvalColorVariable()
        {
        }

        public EvalColorVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
