namespace Bibim
{
    Rectangle::Rectangle()
        : X(0), Y(0), Width(0), Height(0)
    {
    }

    Rectangle::Rectangle(int x, int y, int width, int height)
        : X(x), Y(y), Width(width), Height(height)
    {
    }

    Rectangle::Rectangle(Point leftTop, Point rightBottom)
        : X(leftTop.X),
          Y(leftTop.Y),
          Width(rightBottom.X - leftTop.X),
          Height(rightBottom.Y - leftTop.Y)
    {
    }

    Rectangle::Rectangle(const Rectangle& original)
        : X(original.X), Y(original.Y), Width(original.Width), Height(original.Height)
    {
    }

    int Rectangle::GetLeft() const
    {
        return X;
    }

    int Rectangle::GetTop() const
    {
        return Y;
    }

    int Rectangle::GetRight() const
    {
        return X + Width;
    }

    int Rectangle::GetBottom() const
    {
        return Y + Height;
    }

    int Rectangle::GetCenter() const
    {
        return X + Width / 2;
    }

    int Rectangle::GetMiddle() const
    {
        return Y + Height / 2;
    }

    Point Rectangle::GetCenterPoint() const
    {
        return Point(GetCenter(), GetMiddle());
    }

    void Rectangle::SetLeft(int value)
    {
        const int right = GetRight();

        X = value;
        Width = right - X;
    }

    void Rectangle::SetTop(int value)
    {
        const int bottom = GetBottom();

        Y = value;
        Height = bottom - Y;
    }

    void Rectangle::SetRight(int value)
    {
        Width = value - X;
    }

    void Rectangle::SetBottom(int value)
    {
        Height = value - Y;
    }

    bool Rectangle::Contains(Point p) const
    {
        return GetLeft() <= p.X && p.X <= GetRight() &&
               GetTop()  <= p.Y && p.Y <= GetBottom();
    }

    bool Rectangle::IsEmpty() const
    {
        return Width == 0 || Height == 0;
    }

    Rectangle& Rectangle::operator = (const Rectangle& original)
    {
        X      = original.X;
        Y      = original.Y;
        Width  = original.Width;
        Height = original.Height;
        return *this;
    }

    bool Rectangle::operator == (const Rectangle& right) const
    {
        return X == right.X && Y == right.Y && Width == right.Width && Height == right.Height;
    }

    bool Rectangle::operator != (const Rectangle& right) const
    {
        return !operator == (right);
    }
}