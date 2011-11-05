using System;

namespace Bibim.Animation
{
    [ClassID('e', 'r', 'l', '_')]
    public sealed class EvalLongIntRangedSequence : EvalRangedSequenceTemplate<long, LongIntSequence>
    {
        protected override long Interpolate(long a, long b, float t)
        {
            return (long)((double)a + ((double)(b - a)) * t);
        }
    }
}