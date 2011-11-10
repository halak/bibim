using System;

namespace Bibim.Animation
{
    [ClassID('e', 'r', 'b', '_')]
    public sealed class EvalBoolRangedSequence : EvalRangedSequenceTemplate<bool, BoolSequence>
    {
        protected override bool Interpolate(bool a, bool b, float t)
        {
            return a;
        }
    }
}