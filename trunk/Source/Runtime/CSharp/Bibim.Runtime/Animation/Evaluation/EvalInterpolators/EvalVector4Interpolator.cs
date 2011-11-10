using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'I', 'v', '4')]
    public sealed class EvalVector4Interpolator : EvalInterpolatorTemplate<Vector4>
    {
        public override Vector4 Interpolate(Vector4 a, Vector4 b, float t)
        {
            return Vector4.Lerp(a, b, t);
        }
    }
}
