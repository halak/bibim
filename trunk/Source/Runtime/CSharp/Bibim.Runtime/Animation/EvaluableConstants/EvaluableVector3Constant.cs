using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'v', '3')]
    public sealed class EvaluableVector3Constant : EvaluableConstantTemplate<Vector3>
    {
        #region Constructors
        public EvaluableVector3Constant()
        {
        }

        public EvaluableVector3Constant(Vector3 value)
            : base(value)
        {
        }
        #endregion
    }
}
