using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'v', '3')]
    public sealed class EvalVector3Constant : EvalConstantTemplate<Vector3>
    {
        #region Constructors
        public EvalVector3Constant()
        {
        }

        public EvalVector3Constant(Vector3 value)
            : base(value)
        {
        }
        #endregion
    }
}
