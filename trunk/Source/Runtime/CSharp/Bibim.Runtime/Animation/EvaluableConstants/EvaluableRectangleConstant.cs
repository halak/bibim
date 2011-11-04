using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'r', '_')]
    public sealed class EvaluableRectangleConstant : EvaluableConstantTemplate<Rectangle>
    {
        #region Constructors
        public EvaluableRectangleConstant()
        {
        }

        public EvaluableRectangleConstant(Rectangle value)
            : base(value)
        {
        }
        #endregion
    }
}
