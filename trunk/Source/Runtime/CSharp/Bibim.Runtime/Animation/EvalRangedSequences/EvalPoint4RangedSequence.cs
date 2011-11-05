using System;

namespace Bibim.Animation
{
    [ClassID('e', 'r', 'p', '4')]
    public sealed class EvalPoint4RangedSequence : EvalRangedSequenceTemplate<Point4, Point4Sequence>
    {
        protected override Point4 Interpolate(Point4 a, Point4 b, float t)
        {
            Point4 result = Point4.Zero;
            result.X = (int)((float)a.X + ((float)(b.X - a.X)) * t);
            result.Y = (int)((float)a.Y + ((float)(b.Y - a.Y)) * t);
            result.Z = (int)((float)a.Z + ((float)(b.Z - a.Z)) * t);
            result.W = (int)((float)a.W + ((float)(b.W - a.W)) * t);
            return result;
        }
    }
}