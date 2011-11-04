using System;

namespace Bibim.Animation
{
    [ClassID('e', 's', 'b', '_')]
    public sealed class EvaluableBoolSequence : EvaluableSequenceTemplate<bool, BoolSequence>
    {
        protected override bool Interpolate(bool a, bool b, float t)
        {
            return a;
        }
    }
}