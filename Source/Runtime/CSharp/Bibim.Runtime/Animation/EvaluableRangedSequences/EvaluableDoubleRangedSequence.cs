using System;

namespace Bibim.Animation
{
    [ClassID('e', 'r', 'd', '_')]
    public sealed class EvaluableDoubleRangedSequence : EvaluableRangedSequenceTemplate<double, DoubleSequence>
    {
        protected override double Interpolate(double a, double b, float t)
        {
            return a + (b - a) * (double)t;
        }
    }
}