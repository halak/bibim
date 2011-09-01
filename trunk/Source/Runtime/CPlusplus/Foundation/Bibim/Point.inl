namespace Bibim
{
    Point::Point()
        : X(0), Y(0)
    {
    }

    Point::Point(int x, int y)
        : X(x), Y(y)
    {
    }

    Point::Point(const Point& original)
        : X(original.X), Y(original.Y)
    {
    }

    Point& Point::operator = (const Point& original)
    {
        X = original.X;
        Y = original.Y;
        return *this;
    }

    Point& Point::operator += (const Point& right)
    {
        X += right.X;
        Y += right.Y;
        return *this;
    }

    Point& Point::operator -= (const Point& right)
    {
        X -= right.X;
        Y -= right.Y;
        return *this;
    }

    Point Point::operator + (const Point& right) const
    {
        return Point(X + right.X, Y + right.Y);
    }

    Point Point::operator - (const Point& right) const
    {
        return Point(X - right.X, Y - right.Y);
    }

    bool Point::operator == (const Point& right) const
    {
        return X == right.X && Y == right.Y;
    }

    bool Point::operator != (const Point& right) const
    {
        return !operator == (right);
    }
}