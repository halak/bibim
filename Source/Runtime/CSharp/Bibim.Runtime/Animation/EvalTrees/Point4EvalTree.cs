using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 't', 'p', '4')]
    public sealed class Point4EvalTree : EvalTreeTemplate<Point4>
    {
        #region Constructors
        public Point4EvalTree()
        {
        }

        public Point4EvalTree(Eval<Point4> root)
            : base(root)
        {
        }
        #endregion
    }
}
