using System;

namespace Bibim.Animation
{
    [ClassID('e', 's', 'i', '_')]
    public sealed class EvaluableIntSequence : EvaluableSequenceTemplate<int, IntSequence>
    {
        protected override int Interpolate(int a, int b, float t)
        {
            return (int)((float)a + ((float)(b - a)) * t);
        }
    }
}