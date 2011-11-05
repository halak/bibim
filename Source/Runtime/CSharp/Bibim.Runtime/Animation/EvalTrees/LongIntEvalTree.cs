using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 't', 'l', '_')]
    public sealed class LongIntEvalTree : EvalTreeTemplate<long>
    {
        #region Constructors
        public LongIntEvalTree()
        {
        }

        public LongIntEvalTree(Eval<long> root)
            : base(root)
        {
        }
        #endregion
    }
}
