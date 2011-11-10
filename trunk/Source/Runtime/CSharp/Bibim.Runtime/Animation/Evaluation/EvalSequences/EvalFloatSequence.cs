using System;

namespace Bibim.Animation
{
    [ClassID('e', 's', 'f', '_')]
    public sealed class EvalFloatSequence : EvalSequenceTemplate<float, FloatSequence>
    {
        protected override float Interpolate(float a, float b, float t)
        {
            return a + (b - a) * t;
        }
    }
}