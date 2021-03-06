﻿using System;

namespace Bibim.Animation
{
    [ClassID('e', 's', 'd', '_')]
    public sealed class EvalDoubleSequence : EvalSequenceTemplate<double, DoubleSequence>
    {
        protected override double Interpolate(double a, double b, float t)
        {
            return a + (b - a) * (double)t;
        }
    }
}