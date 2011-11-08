using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 'I', 'f', '_')]
    public sealed class EvalFloatInterpolator : EvalInterpolatorTemplate<float>
    {
        public override float Interpolate(float a, float b, float t)
        {
            return a + (b - a) * t;
        }
    }
}
