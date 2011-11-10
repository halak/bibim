using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 'I', 'i', '_')]
    public sealed class EvalIntInterpolator : EvalInterpolatorTemplate<int>
    {
        public override int Interpolate(int a, int b, float t)
        {
            return MathExtension.Lerp(a, b, t);
        }
    }
}
