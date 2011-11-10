using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 't', 'R', 'f')]
    public sealed class RectFEvalTree : EvalTreeTemplate<RectangleF>
    {
        #region Constructors
        public RectFEvalTree()
        {
        }

        public RectFEvalTree(Eval<RectangleF> root)
            : base(root)
        {
        }
        #endregion
    }
}
