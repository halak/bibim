using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 'r', 'p', '_')]
    public sealed class EvaluablePointRangedSequence : EvaluableRangedSequenceTemplate<Point, PointSequence>
    {
        protected override Point Interpolate(Point a, Point b, float t)
        {
            Point result = Point.Zero;
            result.X = (int)((float)a.X + ((float)(b.X - a.X)) * t);
            result.Y = (int)((float)a.Y + ((float)(b.Y - a.Y)) * t);
            return result;
        }
    }
}