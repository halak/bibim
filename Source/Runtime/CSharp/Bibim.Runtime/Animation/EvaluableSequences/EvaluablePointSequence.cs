using System;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [ClassID('e', 's', 'p', '_')]
    public sealed class EvaluablePointSequence : EvaluableSequenceTemplate<Point, PointSequence>
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