using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 't', 'v', '2')]
    public sealed class Vector2EvalTree : EvalTreeTemplate<Vector2>
    {
        #region Constructors
        public Vector2EvalTree()
        {
        }

        public Vector2EvalTree(Eval<Vector2> root)
            : base(root)
        {
        }
        #endregion
    }
}
