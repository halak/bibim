using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 't', 'v', '4')]
    public sealed class Vector4EvalTree : EvalTreeTemplate<Vector4>
    {
        #region Constructors
        public Vector4EvalTree()
        {
        }

        public Vector4EvalTree(Eval<Vector4> root)
            : base(root)
        {
        }
        #endregion
    }
}
