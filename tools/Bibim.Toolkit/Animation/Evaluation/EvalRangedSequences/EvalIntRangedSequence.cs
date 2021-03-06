﻿using System;

namespace Bibim.Animation
{
    [ClassID('e', 'r', 'i', '_')]
    public sealed class EvalIntRangedSequence : EvalRangedSequenceTemplate<int, IntSequence>
    {
        protected override int Interpolate(int a, int b, float t)
        {
            return (int)((float)a + ((float)(b - a)) * t);
        }
    }
}