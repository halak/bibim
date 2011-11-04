using System;

namespace Bibim.Animation
{
    [ClassID('e', 'r', 'r', '_')]
    public sealed class EvaluableShortIntRangedSequence : EvaluableRangedSequenceTemplate<short, ShortIntSequence>
    {
        protected override short Interpolate(short a, short b, float t)
        {
            return (short)((float)a + ((float)(b - a)) * t);
        }
    }
}