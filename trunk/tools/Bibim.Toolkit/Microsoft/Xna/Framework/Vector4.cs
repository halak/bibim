using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Microsoft.Xna.Framework
{
    public struct Vector4
    {
        public static readonly Vector4 Zero = new Vector4(0.0f, 0.0f, 0.0f, 0.0f);

        public float X;
        public float Y;
        public float Z;
        public float W;

        public Vector4(float x, float y, float z, float w)
        {
            X = x;
            Y = y;
            Z = z;
            W = w;
        }

        public override bool Equals(object obj)
        {
            if (obj.GetType() == typeof(Vector4))
                return this == (Vector4)obj;
            else
                return base.Equals(obj);
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        public static Vector4 Lerp(Vector4 a, Vector4 b, float t)
        {
            return new Vector4(Bibim.MathExtension.Lerp(a.X, b.X, t),
                               Bibim.MathExtension.Lerp(a.Y, b.Y, t),
                               Bibim.MathExtension.Lerp(a.Z, b.Z, t),
                               Bibim.MathExtension.Lerp(a.W, b.W, t));
        }

        public static bool operator ==(Vector4 lhs, Vector4 rhs)
        {
            return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z && lhs.W == rhs.W;
        }

        public static bool operator !=(Vector4 lhs, Vector4 rhs)
        {
            return !(lhs == rhs);
        }
    }
}
