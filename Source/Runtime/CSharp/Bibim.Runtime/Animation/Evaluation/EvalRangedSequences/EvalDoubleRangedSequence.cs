using System;

namespace Bibim.Animation
{
    [ClassID('e', 'r', 'd', '_')]
    public sealed class EvalDoubleRangedSequence : EvalRangedSequenceTemplate<double, DoubleSequence>
    {
        protected override double Interpolate(double a, double b, float t)
        {
            return a + (b - a) * (double)t;
        }
    }
}