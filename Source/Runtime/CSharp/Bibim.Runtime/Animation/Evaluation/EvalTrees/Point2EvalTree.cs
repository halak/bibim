using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 't', 'p', '2')]
    public sealed class Point2EvalTree : EvalTreeTemplate<Point2>
    {
        #region Constructors
        public Point2EvalTree()
        {
        }

        public Point2EvalTree(Eval<Point2> root)
            : base(root)
        {
        }
        #endregion
    }
}
