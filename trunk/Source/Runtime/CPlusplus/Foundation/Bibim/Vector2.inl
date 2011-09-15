namespace Bibim
{
    Vector2::Vector2()
        : X(0.0f), Y(0.0f)
    {
    }

    Vector2::Vector2(int x, int y)
        : X(static_cast<float>(x)), Y(static_cast<float>(y))
    {
    }

    Vector2::Vector2(float x, float y)
        : X(x), Y(y)
    {
    }

    Vector2::Vector2(const Vector2& original)
        : X(original.X), Y(original.Y)
    {
    }

    float Vector2::Dot(Vector2 right) const
    {
        return (X * right.X) + (Y * right.Y);
    }

    Vector2 Vector2::operator + () const
    {
        return Vector2(+X, +Y);
    }

    Vector2 Vector2::operator - () const
    {
        return Vector2(-X, -Y);
    }

    Vector2& Vector2::operator = (const Vector2& right)
    {
        X = right.X;
        Y = right.Y;
        return *this;
    }

    Vector2& Vector2::operator += (const Vector2& right)
    {
        X += right.X;
        Y += right.Y;
        return *this;
    }

    Vector2& Vector2::operator -= (const Vector2& right)
    {
        X -= right.X;
        Y -= right.Y;
        return *this;
    }

    Vector2& Vector2::operator *= (float right)
    {
        X *= right;
        Y *= right;
        return *this;
    }

    Vector2& Vector2::operator /= (float right)
    {
        X /= right;
        Y /= right;
        return *this;
    }

    Vector2 Vector2::operator + (const Vector2& right) const
    {
        return Vector2(X + right.X, Y + right.Y);
    }

    Vector2 Vector2::operator - (const Vector2& right) const
    {
        return Vector2(X - right.X, Y - right.Y);
    }

    Vector2 Vector2::operator * (float right) const
    {
        return Vector2(X * right, Y * right);
    }

    Vector2 Vector2::operator / (float right) const
    {
        return Vector2(X / right, Y / right);
    }

    bool Vector2::operator == (const Vector2& right) const
    {
        return X == right.X && Y == right.Y;
    }

    bool Vector2::operator != (const Vector2& right) const
    {
        return !operator == (right);
    }

    Vector2 operator * (float left, const Vector2& right)
    {
        return Vector2(left * right.X, left * right.Y);
    }
}