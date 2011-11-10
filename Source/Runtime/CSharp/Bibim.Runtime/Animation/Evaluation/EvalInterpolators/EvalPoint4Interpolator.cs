using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 'I', 'p', '4')]
    public sealed class EvalPoint4Interpolator : EvalInterpolatorTemplate<Point4>
    {
        public override Point4 Interpolate(Point4 a, Point4 b, float t)
        {
            return Point4.Lerp(a, b, t);
        }
    }
}
