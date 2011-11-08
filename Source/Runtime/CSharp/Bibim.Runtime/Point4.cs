using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim
{
    public struct Point4
    {
        public static readonly Point4 Zero = new Point4();

        public int X;
        public int Y;
        public int Z;
        public int W;

        public Point4(int x, int y, int z, int w)
        {
            X = x;
            Y = y;
            Z = z;
            W = w;
        }

        public Point4(Point4 original)
        {
            X = original.X;
            Y = original.Y;
            Z = original.Z;
            W = original.W;
        }

        public static Point4 Lerp(Point4 value1, Point4 value2, float amount)
        {
            Point4 result = Point4.Zero;
            result.X = value1.X + (int)(((float)(value2.X - value1.X)) * amount);
            result.Y = value1.Y + (int)(((float)(value2.Y - value1.Y)) * amount);
            result.Z = value1.Z + (int)(((float)(value2.Z - value1.Z)) * amount);
            result.W = value1.W + (int)(((float)(value2.W - value1.W)) * amount);
            return result;
        }
    }
}
