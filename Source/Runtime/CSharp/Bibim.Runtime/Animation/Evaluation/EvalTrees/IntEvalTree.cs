using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 't', 'i', '_')]
    public sealed class IntEvalTree : EvalTreeTemplate<int>
    {
        #region Constructors
        public IntEvalTree()
        {
        }

        public IntEvalTree(Eval<int> root)
            : base(root)
        {
        }
        #endregion
    }
}
