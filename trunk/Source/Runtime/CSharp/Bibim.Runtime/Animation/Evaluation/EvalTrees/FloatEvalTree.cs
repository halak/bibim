using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 't', 'f', '_')]
    public sealed class FloatEvalTree : EvalTreeTemplate<float>
    {
        #region Constructors
        public FloatEvalTree()
        {
        }

        public FloatEvalTree(Eval<float> root)
            : base(root)
        {
        }
        #endregion
    }
}
