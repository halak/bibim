using System;

namespace Bibim.Animation
{
    [ClassID('e', 'r', 'p', '2')]
    public sealed class EvalPoint2RangedSequence : EvalRangedSequenceTemplate<Point2, Point2Sequence>
    {
        protected override Point2 Interpolate(Point2 a, Point2 b, float t)
        {
            Point2 result = Point2.Zero;
            result.X = (int)((float)a.X + ((float)(b.X - a.X)) * t);
            result.Y = (int)((float)a.Y + ((float)(b.Y - a.Y)) * t);
            return result;
        }
    }
}