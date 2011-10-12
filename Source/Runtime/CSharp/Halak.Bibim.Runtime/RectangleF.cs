using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim
{
    public struct RectF
    {
        public static readonly RectF Empty = new RectF(0.0f, 0.0f, 0.0f, 0.0f);

        public float X;
        public float Y;
        public float Width;
        public float Height;

        public RectF(float x, float y, float width, float height)
        {
            X = x;
            Y = y;
            Width = width;
            Height = height;
        }
    }
}
