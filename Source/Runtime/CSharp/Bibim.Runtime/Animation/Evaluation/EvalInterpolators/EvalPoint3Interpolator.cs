using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 'I', 'p', '3')]
    public sealed class EvalPoint3Interpolator : EvalInterpolatorTemplate<Point3>
    {
        public override Point3 Interpolate(Point3 a, Point3 b, float t)
        {
            return Point3.Lerp(a, b, t);
        }
    }
}
