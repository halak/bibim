using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 't', 'c', '_')]
    public sealed class ColorEvalTree : EvalTreeTemplate<Color>
    {
        #region Constructors
        public ColorEvalTree()
        {
        }

        public ColorEvalTree(Eval<Color> root)
            : base(root)
        {
        }
        #endregion
    }
}
