using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 't', 'v', '3')]
    public sealed class Vector3EvalTree : EvalTreeTemplate<Vector3>
    {
        #region Constructors
        public Vector3EvalTree()
        {
        }

        public Vector3EvalTree(Eval<Vector3> root)
            : base(root)
        {
        }
        #endregion
    }
}
