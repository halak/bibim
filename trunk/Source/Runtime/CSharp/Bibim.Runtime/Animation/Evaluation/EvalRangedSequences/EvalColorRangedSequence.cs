using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'r', 'c', '_')]
    public sealed class EvalColorRangedSequence : EvalRangedSequenceTemplate<Color, ColorSequence>
    {
        protected override Color Interpolate(Color a, Color b, float t)
        {
            return Color.Lerp(a, b, t);
        }
    }
}