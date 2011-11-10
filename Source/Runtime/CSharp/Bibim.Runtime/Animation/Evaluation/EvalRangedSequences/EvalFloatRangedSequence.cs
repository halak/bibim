using System;

namespace Bibim.Animation
{
    [ClassID('e', 'r', 'f', '_')]
    public sealed class EvalFloatRangedSequence : EvalRangedSequenceTemplate<float, FloatSequence>
    {
        protected override float Interpolate(float a, float b, float t)
        {
            return a + (b - a) * t;
        }
    }
}