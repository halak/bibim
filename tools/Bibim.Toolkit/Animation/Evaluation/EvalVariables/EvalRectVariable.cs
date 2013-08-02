﻿using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'r', '_')]
    public sealed class EvalRectVariable : EvalVariableTemplate<Rectangle>
    {
        #region Constructors
        public EvalRectVariable()
        {
        }

        public EvalRectVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
