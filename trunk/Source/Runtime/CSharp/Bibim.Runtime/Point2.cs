using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim
{
    public struct Point2
    {
        public static readonly Point2 Zero = new Point2();

        public int X;
        public int Y;

        public Point2(int x, int y)
        {
            X = x;
            Y = y;
        }

        public Point2(Point2 original)
        {
            X = original.X;
            Y = original.Y;
        }

        public static Point2 Lerp(Point2 value1, Point2 value2, float amount)
        {
            Point2 result = Point2.Zero;
            result.X = value1.X + (int)(((float)(value2.X - value1.X)) * amount);
            result.Y = value1.Y + (int)(((float)(value2.Y - value1.Y)) * amount);
            return result;
        }
    }
}
