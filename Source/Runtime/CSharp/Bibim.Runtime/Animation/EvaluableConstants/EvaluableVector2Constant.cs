using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'v', '2')]
    public sealed class EvaluableVector2Constant : EvaluableConstantTemplate<Vector2>
    {
        #region Constructors
        public EvaluableVector2Constant()
        {
        }

        public EvaluableVector2Constant(Vector2 value)
            : base(value)
        {
        }
        #endregion
    }
}
