using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'r', '_')]
    public sealed class EvalRectangleConstant : EvalConstantTemplate<Rectangle>
    {
        #region Constructors
        public EvalRectangleConstant()
        {
        }

        public EvalRectangleConstant(Rectangle value)
            : base(value)
        {
        }
        #endregion
    }
}
