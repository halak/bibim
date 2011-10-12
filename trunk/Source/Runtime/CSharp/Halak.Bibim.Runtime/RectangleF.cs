using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim
{
    public struct RectangleF
    {
        public static readonly RectangleF Empty = new RectangleF(0.0f, 0.0f, 0.0f, 0.0f);

        public float X;
        public float Y;
        public float Width;
        public float Height;

        public RectangleF(float x, float y, float width, float height)
        {
            X = x;
            Y = y;
            Width = width;
            Height = height;
        }
    }
}
