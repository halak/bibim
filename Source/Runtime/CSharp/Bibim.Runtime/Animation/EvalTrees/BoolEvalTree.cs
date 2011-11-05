using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 't', 'b', '_')]
    public sealed class BoolEvalTree : EvalTreeTemplate<bool>
    {
        #region Constructors
        public BoolEvalTree()
        {
        }

        public BoolEvalTree(Eval<bool> root)
            : base(root)
        {
        }
        #endregion
    }
}
