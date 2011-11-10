using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 't', 'r', '_')]
    public sealed class RectEvalTree : EvalTreeTemplate<Rectangle>
    {
        #region Constructors
        public RectEvalTree()
        {
        }

        public RectEvalTree(Eval<Rectangle> root)
            : base(root)
        {
        }
        #endregion
    }
}
