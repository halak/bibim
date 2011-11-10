using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 'I', 'l', '_')]
    public sealed class EvalLongIntInterpolator : EvalInterpolatorTemplate<long>
    {
        public override long Interpolate(long a, long b, float t)
        {
            return MathExtension.Lerp(a, b, t);
        }
    }
}
