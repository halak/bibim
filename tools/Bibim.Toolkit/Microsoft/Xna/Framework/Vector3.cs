using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Microsoft.Xna.Framework
{
    public struct Vector3
    {
        public static readonly Vector3 Zero = new Vector3(0.0f, 0.0f, 0.0f);

        public float X;
        public float Y;
        public float Z;

        public Vector3(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public override bool Equals(object obj)
        {
            if (obj.GetType() == typeof(Vector3))
                return this == (Vector3)obj;
            else
                return base.Equals(obj);
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        public static Vector3 Lerp(Vector3 a, Vector3 b, float t)
        {
            return new Vector3(Bibim.MathExtension.Lerp(a.X, b.X, t),
                               Bibim.MathExtension.Lerp(a.Y, b.Y, t),
                               Bibim.MathExtension.Lerp(a.Z, b.Z, t));
        }

        public static bool operator ==(Vector3 lhs, Vector3 rhs)
        {
            return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z;
        }

        public static bool operator !=(Vector3 lhs, Vector3 rhs)
        {
            return !(lhs == rhs);
        }
    }
}
