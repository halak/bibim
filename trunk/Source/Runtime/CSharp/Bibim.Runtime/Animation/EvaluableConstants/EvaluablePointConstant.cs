using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'p', '_')]
    public sealed class EvaluablePointConstant : EvaluableConstantTemplate<Point>
    {
        #region Constructors
        public EvaluablePointConstant()
        {
        }

        public EvaluablePointConstant(Point value)
            : base(value)
        {
        }
        #endregion
    }
}
