using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'v', '2')]
    public sealed class EvalVector2Constant : EvalConstantTemplate<Vector2>
    {
        #region Constructors
        public EvalVector2Constant()
        {
        }

        public EvalVector2Constant(Vector2 value)
            : base(value)
        {
        }
        #endregion
    }
}
