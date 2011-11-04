using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'r', '_')]
    public sealed class EvaluableRectangleVariable : EvaluableVariableTemplate<Rectangle>
    {
        #region Constructors
        public EvaluableRectangleVariable()
        {
        }

        public EvaluableRectangleVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
