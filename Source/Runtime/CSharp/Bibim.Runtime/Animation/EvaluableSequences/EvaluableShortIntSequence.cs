using System;

namespace Bibim.Animation
{
    [ClassID('e', 's', 's', '_')]
    public sealed class EvaluableShortIntSequence : EvaluableSequenceTemplate<short, ShortIntSequence>
    {
        protected override short Interpolate(short a, short b, float t)
        {
            return (short)((float)a + ((float)(b - a)) * t);
        }
    }
}