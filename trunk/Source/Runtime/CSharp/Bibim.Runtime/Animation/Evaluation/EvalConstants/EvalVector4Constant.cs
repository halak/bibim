using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'v', '4')]
    public sealed class EvalVector4Constant : EvalConstantTemplate<Vector4>
    {
        #region Constructors
        public EvalVector4Constant()
        {
        }

        public EvalVector4Constant(Vector4 value)
            : base(value)
        {
        }
        #endregion
    }
}
