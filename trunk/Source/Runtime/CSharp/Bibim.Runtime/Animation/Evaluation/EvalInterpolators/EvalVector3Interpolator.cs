using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'I', 'v', '3')]
    public sealed class EvalVector3Interpolator : EvalInterpolatorTemplate<Vector3>
    {
        public override Vector3 Interpolate(Vector3 a, Vector3 b, float t)
        {
            return Vector3.Lerp(a, b, t);
        }
    }
}
