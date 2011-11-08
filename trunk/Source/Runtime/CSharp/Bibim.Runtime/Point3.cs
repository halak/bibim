using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim
{
    public struct Point3
    {
        public static readonly Point3 Zero = new Point3();

        public int X;
        public int Y;
        public int Z;

        public Point3(int x, int y, int z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public Point3(Point3 original)
        {
            X = original.X;
            Y = original.Y;
            Z = original.Z;
        }

        public static Point3 Lerp(Point3 value1, Point3 value2, float amount)
        {
            Point3 result = Point3.Zero;
            result.X = value1.X + (int)(((float)(value2.X - value1.X)) * amount);
            result.Y = value1.Y + (int)(((float)(value2.Y - value1.Y)) * amount);
            result.Z = value1.Z + (int)(((float)(value2.Z - value1.Z)) * amount);
            return result;
        }
    }
}
