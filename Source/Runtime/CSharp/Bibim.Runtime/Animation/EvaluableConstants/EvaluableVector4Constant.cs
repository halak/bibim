using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'v', '4')]
    public sealed class EvaluableVector4Constant : EvaluableConstantTemplate<Vector4>
    {
        #region Constructors
        public EvaluableVector4Constant()
        {
        }

        public EvaluableVector4Constant(Vector4 value)
            : base(value)
        {
        }
        #endregion
    }
}
