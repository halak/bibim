using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 'I', 'd', '_')]
    public sealed class EvalDoubleInterpolator : EvalInterpolatorTemplate<double>
    {
        public override double Interpolate(double a, double b, float t)
        {
            return a + (b - a) * ((double)t);
        }
    }
}
