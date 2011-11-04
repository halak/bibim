using System;

namespace Bibim.Animation
{
    [ClassID('e', 's', 'l', '_')]
    public sealed class EvaluableLongIntSequence : EvaluableSequenceTemplate<long, LongIntSequence>
    {
        protected override long Interpolate(long a, long b, float t)
        {
            return (long)((double)a + ((double)(b - a)) * t);
        }
    }
}