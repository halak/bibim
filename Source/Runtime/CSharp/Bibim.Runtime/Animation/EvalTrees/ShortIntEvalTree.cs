using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 't', 's', '_')]
    public sealed class ShortIntEvalTree : EvalTreeTemplate<short>
    {
        #region Constructors
        public ShortIntEvalTree()
        {
        }

        public ShortIntEvalTree(Eval<short> root)
            : base(root)
        {
        }
        #endregion
    }
}
