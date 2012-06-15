namespace Bibim
{
    Point4::Point4()
        : X(0), Y(0), Z(0), W(0)
    {
    }

    Point4::Point4(int x, int y, int z, int w)
        : X(x), Y(y), Z(z), W(w)
    {
    }

    Point4::Point4(const Point4& original)
        : X(original.X), Y(original.Y), Z(original.Z), W(original.W)
    {
    }

    Point4 Point4::operator + () const
    {
        return Point4(+X, +Y, +Z, +W);
    }

    Point4 Point4::operator - () const
    {
        return Point4(-X, -Y, -Z, -W);
    }

    Point4& Point4::operator = (const Point4& right)
    {
        X = right.X;
        Y = right.Y;
        Z = right.Z;
        W = right.W;
        return *this;
    }

    Point4& Point4::operator += (const Point4& right)
    {
        X += right.X;
        Y += right.Y;
        Z += right.Z;
        W += right.W;
        return *this;
    }

    Point4& Point4::operator -= (const Point4& right)
    {
        X -= right.X;
        Y -= right.Y;
        Z -= right.Z;
        W -= right.W;
        return *this;
    }

    Point4& Point4::operator *= (int right)
    {
        X *= right;
        Y *= right;
        Z *= right;
        W *= right;
        return *this;
    }

    Point4& Point4::operator /= (int right)
    {
        X /= right;
        Y /= right;
        Z /= right;
        W /= right;
        return *this;
    }

    Point4 Point4::operator + (const Point4& right) const
    {
        return Point4(X + right.X, Y + right.Y, Z + right.Z, W + right.W);
    }

    Point4 Point4::operator - (const Point4& right) const
    {
        return Point4(X - right.X, Y - right.Y, Z - right.Z, W - right.W);
    }

    Point4 Point4::operator * (int right) const
    {
        return Point4(X * right, Y * right, Z * right, W * right);
    }

    Point4 Point4::operator / (int right) const
    {
        return Point4(X / right, Y / right, Z / right, W / right);
    }

    bool Point4::operator == (const Point4& right) const
    {
        return X == right.X && Y == right.Y && Z == right.Z && W == right.W;
    }

    bool Point4::operator != (const Point4& right) const
    {
        return !operator == (right);
    }
}