using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Microsoft.Xna.Framework
{
    public struct Rectangle
    {
        public static readonly Rectangle Empty = new Rectangle(0, 0, 0, 0);

        public int X;
        public int Y;
        public int Width;
        public int Height;

        public Rectangle(int x, int y, int width, int height)
        {
            X = x;
            Y = y;
            Width = width;
            Height = height;
        }
    }
}
