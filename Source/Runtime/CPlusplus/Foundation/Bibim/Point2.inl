namespace Bibim
{
    Point2::Point2()
        : X(0), Y(0)
    {
    }

    Point2::Point2(int x, int y)
        : X(x), Y(y)
    {
    }

    Point2::Point2(const Point2& original)
        : X(original.X), Y(original.Y)
    {
    }

    Point2& Point2::operator = (const Point2& right)
    {
        X = right.X;
        Y = right.Y;
        return *this;
    }

    Point2& Point2::operator += (const Point2& right)
    {
        X += right.X;
        Y += right.Y;
        return *this;
    }

    Point2& Point2::operator -= (const Point2& right)
    {
        X -= right.X;
        Y -= right.Y;
        return *this;
    }

    Point2 Point2::operator + (const Point2& right) const
    {
        return Point2(X + right.X, Y + right.Y);
    }

    Point2 Point2::operator - (const Point2& right) const
    {
        return Point2(X - right.X, Y - right.Y);
    }

    bool Point2::operator == (const Point2& right) const
    {
        return X == right.X && Y == right.Y;
    }

    bool Point2::operator != (const Point2& right) const
    {
        return !operator == (right);
    }
}