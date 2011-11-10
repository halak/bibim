using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('e', 'I', 'p', '2')]
    public sealed class EvalPoint2Interpolator : EvalInterpolatorTemplate<Point2>
    {
        public override Point2 Interpolate(Point2 a, Point2 b, float t)
        {
            return Point2.Lerp(a, b, t);
        }
    }
}
