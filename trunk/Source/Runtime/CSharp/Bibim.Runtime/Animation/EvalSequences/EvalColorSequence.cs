using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 's', 'c', '_')]
    public sealed class EvalColorSequence : EvalSequenceTemplate<Color, ColorSequence>
    {
        protected override Color Interpolate(Color a, Color b, float t)
        {
            return Color.Lerp(a, b, t);
        }
    }
}