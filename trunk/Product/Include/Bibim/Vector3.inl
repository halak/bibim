namespace Bibim
{
    Vector3::Vector3()
        : X(0.0f), Y(0.0f), Z(0.0f)
    {
    }

    Vector3::Vector3(int x, int y, int z)
        : X(static_cast<float>(x)), Y(static_cast<float>(y)), Z(static_cast<float>(z))
    {
    }

    Vector3::Vector3(float x, float y, float z)
        : X(x), Y(y), Z(z)
    {
    }

    Vector3::Vector3(Vector2 xy, float z)
        : X(xy.X), Y(xy.Y), Z(z)
    {
    }

    Vector3::Vector3(const Vector3& original)
        : X(original.X), Y(original.Y), Z(original.Z)
    {
    }
        
    float Vector3::Dot(Vector3 right) const
    {
        return X * right.X + Y * right.Y + Z * right.Z;
    }

    Vector3 Vector3::Cross(Vector3 right) const
    {
        return Vector3(Y * right.Z - Z * right.Y,
                       Z * right.X - X * right.Z,
                       X * right.Y - Y * right.X);
    }

    Vector3 Vector3::operator + () const
    {
        return Vector3(+X, +Y, +Z);
    }

    Vector3 Vector3::operator - () const
    {
        return Vector3(-X, -Y, -Z);
    }

    Vector3& Vector3::operator = (const Vector3& right)
    {
        X = right.X;
        Y = right.Y;
        Z = right.Z;
        return *this;
    }

    Vector3& Vector3::operator += (const Vector3& right)
    {
        X += right.X;
        Y += right.Y;
        Z += right.Z;
        return *this;
    }

    Vector3& Vector3::operator -= (const Vector3& right)
    {
        X -= right.X;
        Y -= right.Y;
        Z -= right.Z;
        return *this;
    }

    Vector3& Vector3::operator *= (float right)
    {
        X *= right;
        Y *= right;
        Z *= right;
        return *this;
    }

    Vector3& Vector3::operator /= (float right)
    {
        X /= right;
        Y /= right;
        Z /= right;
        return *this;
    }

    Vector3 Vector3::operator + (const Vector3& right) const
    {
        return Vector3(X + right.X, Y + right.Y, Z + right.Z);
    }

    Vector3 Vector3::operator - (const Vector3& right) const
    {
        return Vector3(X - right.X, Y - right.Y, Z - right.Z);
    }

    Vector3 Vector3::operator * (float right) const
    {
        return Vector3(X * right, Y * right, Z * right);
    }

    Vector3 Vector3::operator / (float right) const
    {
        return Vector3(X / right, Y / right, Z / right);
    }

    bool Vector3::operator == (const Vector3& right) const
    {
        return X == right.X && Y == right.Y && Z == right.Z;
    }

    bool Vector3::operator != (const Vector3& right) const
    {
        return !operator == (right);
    }

    Vector3 operator * (float left, const Vector3& right)
    {
        return Vector3(left * right.X, left * right.Y, left * right.Z);
    }
}