using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'I', 'v', '2')]
    public sealed class EvalVector2Interpolator : EvalInterpolatorTemplate<Vector2>
    {
        public override Vector2 Interpolate(Vector2 a, Vector2 b, float t)
        {
            return Vector2.Lerp(a, b, t);
        }
    }
}
