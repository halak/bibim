using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 't', 'p', '3')]
    public sealed class Point3EvalTree : EvalTreeTemplate<Point3>
    {
        #region Constructors
        public Point3EvalTree()
        {
        }

        public Point3EvalTree(Eval<Point3> root)
            : base(root)
        {
        }
        #endregion
    }
}
