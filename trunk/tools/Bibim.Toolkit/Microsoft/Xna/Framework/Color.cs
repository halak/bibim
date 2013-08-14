using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Microsoft.Xna.Framework
{
    public struct Color
    {
        public static readonly Color Black = new Color(0, 0, 0);
        public static readonly Color White = new Color(255, 255, 255);

        public byte R;
        public byte G;
        public byte B;
        public byte A;

        public Color(byte r, byte g, byte b)
            : this(r, g, b, 255)
        {
        }

        public Color(int r, int g, int b)
            : this(Clamp(r), Clamp(g), Clamp(b), 255)
        {
        }

        private Color(byte r, byte g, byte b, byte a)
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }

        public override bool Equals(object obj)
        {
            if (obj.GetType() == typeof(Color))
                return this == (Color)obj;
            else
                return base.Equals(obj);
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        public static Color Lerp(Color a, Color b, float t)
        {
            return new Color(Bibim.MathExtension.Lerp(a.R, b.R, t),
                             Bibim.MathExtension.Lerp(a.G, b.G, t),
                             Bibim.MathExtension.Lerp(a.B, b.B, t),
                             Bibim.MathExtension.Lerp(a.A, b.A, t));
        }

        private static byte Clamp(int value)
        {
            return (byte)(value < 0 ? 0 : (value > 255 ? 255 : value));
        }

        public static bool operator ==(Color lhs, Color rhs)
        {
            return lhs.R == rhs.R && lhs.G == rhs.G && lhs.B == rhs.B && lhs.A == rhs.A;
        }

        public static bool operator !=(Color lhs, Color rhs)
        {
            return !(lhs == rhs);
        }
    }
}
