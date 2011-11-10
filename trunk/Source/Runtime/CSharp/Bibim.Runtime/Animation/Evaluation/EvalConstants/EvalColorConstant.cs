using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'c', '_')]
    public sealed class EvalColorConstant : EvalConstantTemplate<Color>
    {
        #region Constructors
        public EvalColorConstant()
        {
        }

        public EvalColorConstant(Color value)
            : base(value)
        {
        }
        #endregion
    }
}
