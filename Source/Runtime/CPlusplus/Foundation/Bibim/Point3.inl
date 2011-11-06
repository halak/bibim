namespace Bibim
{
    Point3::Point3()
        : X(0), Y(0), Z(0)
    {
    }

    Point3::Point3(int x, int y, int z)
        : X(x), Y(y), Z(z)
    {
    }

    Point3::Point3(const Point3& original)
        : X(original.X), Y(original.Y), Z(original.Z)
    {
    }

    Point3 Point3::operator + () const
    {
        return Point3(+X, +Y, +Z);
    }

    Point3 Point3::operator - () const
    {
        return Point3(-X, -Y, -Z);
    }

    Point3& Point3::operator = (const Point3& right)
    {
        X = right.X;
        Y = right.Y;
        Z = right.Z;
        return *this;
    }

    Point3& Point3::operator += (const Point3& right)
    {
        X += right.X;
        Y += right.Y;
        Z += right.Z;
        return *this;
    }

    Point3& Point3::operator -= (const Point3& right)
    {
        X -= right.X;
        Y -= right.Y;
        Z -= right.Z;
        return *this;
    }

    Point3& Point3::operator *= (int right)
    {
        X *= right;
        Y *= right;
        Z *= right;
        return *this;
    }

    Point3& Point3::operator /= (int right)
    {
        X /= right;
        Y /= right;
        Z /= right;
        return *this;
    }

    Point3 Point3::operator + (const Point3& right) const
    {
        return Point3(X + right.X, Y + right.Y, Z + right.Z);
    }

    Point3 Point3::operator - (const Point3& right) const
    {
        return Point3(X - right.X, Y - right.Y, Z - right.Z);
    }

    Point3 Point3::operator * (int right) const
    {
        return Point3(X * right, Y * right, Z * right);
    }

    Point3 Point3::operator / (int right) const
    {
        return Point3(X / right, Y / right, Z / right);
    }

    bool Point3::operator == (const Point3& right) const
    {
        return X == right.X && Y == right.Y && Z == right.Z;
    }

    bool Point3::operator != (const Point3& right) const
    {
        return !operator == (right);
    }
}