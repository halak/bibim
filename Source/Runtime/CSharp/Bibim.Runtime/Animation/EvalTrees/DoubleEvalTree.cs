using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 't', 'd', '_')]
    public sealed class DoubleEvalTree : EvalTreeTemplate<double>
    {
        #region Constructors
        public DoubleEvalTree()
        {
        }

        public DoubleEvalTree(Eval<double> root)
            : base(root)
        {
        }
        #endregion
    }
}
