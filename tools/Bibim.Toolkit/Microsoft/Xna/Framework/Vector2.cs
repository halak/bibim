using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Microsoft.Xna.Framework
{
    public struct Vector2
    {
        public static readonly Vector2 Zero = new Vector2(0.0f, 0.0f);

        public float X;
        public float Y;

        public Vector2(float x, float y)
        {
            X = x;
            Y = y;
        }

        public override bool Equals(object obj)
        {
            if (obj.GetType() == typeof(Vector2))
                return this == (Vector2)obj;
            else
                return base.Equals(obj);
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        public static Vector2 Lerp(Vector2 a, Vector2 b, float t)
        {
            return new Vector2(Bibim.MathExtension.Lerp(a.X, b.X, t),
                               Bibim.MathExtension.Lerp(a.Y, b.Y, t));
        }
        
        public static Vector2 operator -(Vector2 operand)
        {
            return new Vector2(-operand.X, -operand.Y);
        }

        public static bool operator ==(Vector2 lhs, Vector2 rhs)
        {
            return lhs.X == rhs.X && lhs.Y == rhs.Y;
        }

        public static bool operator !=(Vector2 lhs, Vector2 rhs)
        {
            return !(lhs == rhs);
        }
    }
}
