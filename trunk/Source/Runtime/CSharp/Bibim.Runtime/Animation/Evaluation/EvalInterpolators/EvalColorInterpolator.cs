using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'I', 'c', '_')]
    public sealed class EvalColorInterpolator : EvalInterpolatorTemplate<Color>
    {
        public override Color Interpolate(Color a, Color b, float t)
        {
            return Color.Lerp(a, b, t);
        }
    }
}
