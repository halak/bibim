using System;

namespace Bibim.Animation
{
    [ClassID('e', 's', 'p', '3')]
    public sealed class EvalPoint3Sequence : EvalSequenceTemplate<Point3, Point3Sequence>
    {
        protected override Point3 Interpolate(Point3 a, Point3 b, float t)
        {
            Point3 result = Point3.Zero;
            result.X = (int)((float)a.X + ((float)(b.X - a.X)) * t);
            result.Y = (int)((float)a.Y + ((float)(b.Y - a.Y)) * t);
            result.Z = (int)((float)a.Z + ((float)(b.Z - a.Z)) * t);
            return result;
        }
    }
}