using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'r', '_')]
    public sealed class EvalRectangleVariable : EvalVariableTemplate<Rectangle>
    {
        #region Constructors
        public EvalRectangleVariable()
        {
        }

        public EvalRectangleVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
