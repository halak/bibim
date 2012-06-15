namespace Bibim
{
    byte Color::Add(byte a, byte b)
    {
        return 255 - a < b ? 255 : a + b;
    }

    byte Color::Subtract(byte a, byte b)
    {
        return a > b ? a - b : 0;
    }

    byte Color::Clamp(int value)
    {
        return value < 0 ? 0 : (value > 255 ? 255 : static_cast<byte>(value));
    }

    byte Color::Clamp(float value)
    {
        return value < 0.0f ? 0 : (value > 255.0f ? 255 : static_cast<byte>(value));
    }

    Color::Color()
        : R(0), G(0), B(0), A(0)
    {
    }

    Color::Color(int r, int g, int b)
        : R(Clamp(r)), G(Clamp(g)), B(Clamp(b)), A(255)
    {
    }

    Color::Color(int r, int g, int b, int a)
        : R(Clamp(r)), G(Clamp(g)), B(Clamp(b)), A(Clamp(a))
    {
    }

    Color::Color(unsigned long argb)
        : R(static_cast<byte>((argb & 0x00FF0000) >> 16)),
          G(static_cast<byte>((argb & 0x0000FF00) >> 8)),
          B(static_cast<byte>((argb & 0x000000FF) >> 0)),
          A(static_cast<byte>((argb & 0xFF000000) >> 24))
    {
    }

    Color::Color(Vector3 rgb)
        : R(Clamp(rgb.X * 255.0f)),
          G(Clamp(rgb.Y * 255.0f)),
          B(Clamp(rgb.Z * 255.0f)),
          A(255)
    {
    }

    Color::Color(Vector4 rgba)
        : R(Clamp(rgba.X * 255.0f)),
          G(Clamp(rgba.Y * 255.0f)),
          B(Clamp(rgba.Z * 255.0f)),
          A(Clamp(rgba.W * 255.0f))
    {
    }

    Color::Color(const Color& original)
        : R(original.R), G(original.G), B(original.B), A(original.A)
    {
    }

    Vector3 Color::ToVector3() const
    {
        return Vector3(static_cast<float>(R) / 255.0f, static_cast<float>(G) / 255.0f, static_cast<float>(B) / 255.0f);
    }

    Vector4 Color::ToVector4() const
    {
        return Vector4(static_cast<float>(R) / 255.0f, static_cast<float>(G) / 255.0f, static_cast<float>(B) / 255.0f, static_cast<float>(A) / 255.0f);
    }

    unsigned long Color::ToRGBA() const
    {
        return (static_cast<unsigned long>(R) << 24) |
               (static_cast<unsigned long>(G) << 16) |
               (static_cast<unsigned long>(B) << 8)  |
               (static_cast<unsigned long>(A) << 0);
    }

    unsigned long Color::ToARGB() const
    {
        return (static_cast<unsigned long>(A) << 24) |
               (static_cast<unsigned long>(R) << 16) |
               (static_cast<unsigned long>(G) << 8)  |
               (static_cast<unsigned long>(B) << 0);
    }

    Color& Color::operator = (const Color& right)
    {
        R = right.R;
        G = right.G;
        B = right.B;
        A = right.A;
        return *this;
    }

    Color& Color::operator += (Color right)
    {
        R = Add(R, right.R);
        G = Add(G, right.G);
        B = Add(B, right.B);
        A = Add(A, right.A);
        return *this;
    }

    Color& Color::operator -= (Color right)
    {
        R = Subtract(R, right.R);
        G = Subtract(G, right.G);
        B = Subtract(B, right.B);
        A = Subtract(A, right.A);
        return *this;
    }

    Color& Color::operator *= (Color right)
    {
        R = Clamp(static_cast<float>(R) * (static_cast<float>(right.R) / 255.0f));
        G = Clamp(static_cast<float>(G) * (static_cast<float>(right.G) / 255.0f));
        B = Clamp(static_cast<float>(B) * (static_cast<float>(right.B) / 255.0f));
        A = Clamp(static_cast<float>(A) * (static_cast<float>(right.A) / 255.0f));
        return *this;
    }

    Color& Color::operator *= (float right)
    {
        R = Clamp(static_cast<float>(R) * right);
        G = Clamp(static_cast<float>(G) * right);
        B = Clamp(static_cast<float>(B) * right);
        A = Clamp(static_cast<float>(A) * right);
        return *this;
    }

    Color& Color::operator /= (Color right)
    {
        R = Clamp(static_cast<float>(R) / (static_cast<float>(right.R) / 255.0f));
        G = Clamp(static_cast<float>(G) / (static_cast<float>(right.G) / 255.0f));
        B = Clamp(static_cast<float>(B) / (static_cast<float>(right.B) / 255.0f));
        A = Clamp(static_cast<float>(A) / (static_cast<float>(right.A) / 255.0f));
        return *this;
    }

    Color& Color::operator /= (float right)
    {
        R = Clamp(static_cast<float>(R) / right);
        G = Clamp(static_cast<float>(G) / right);
        B = Clamp(static_cast<float>(B) / right);
        A = Clamp(static_cast<float>(A) / right);
        return *this;
    }

    Color Color::operator + (Color right) const
    {
        return Color(Add(R, right.R),
                     Add(G, right.G),
                     Add(B, right.B),
                     Add(A, right.A));
    }

    Color Color::operator - (Color right) const
    {
        return Color(Subtract(R, right.R),
                     Subtract(G, right.G),
                     Subtract(B, right.B),
                     Subtract(A, right.A));
    }

    Color Color::operator * (Color right) const
    {
        return Color(Clamp(static_cast<float>(R) * (static_cast<float>(right.R) / 255.0f)),
                     Clamp(static_cast<float>(G) * (static_cast<float>(right.G) / 255.0f)),
                     Clamp(static_cast<float>(B) * (static_cast<float>(right.B) / 255.0f)),
                     Clamp(static_cast<float>(A) * (static_cast<float>(right.A) / 255.0f)));
    }

    Color Color::operator * (float right) const
    {
        return Color(Clamp(static_cast<float>(R) * right),
                     Clamp(static_cast<float>(G) * right),
                     Clamp(static_cast<float>(B) * right),
                     Clamp(static_cast<float>(A) * right));
    }

    Color Color::operator / (Color right) const
    {
        return Color(Clamp(static_cast<float>(R) / (static_cast<float>(right.R) / 255.0f)),
                     Clamp(static_cast<float>(G) / (static_cast<float>(right.G) / 255.0f)),
                     Clamp(static_cast<float>(B) / (static_cast<float>(right.B) / 255.0f)),
                     Clamp(static_cast<float>(A) / (static_cast<float>(right.A) / 255.0f)));
    }

    Color Color::operator / (float right) const
    {
        return Color(Clamp(static_cast<float>(R) / right),
                     Clamp(static_cast<float>(G) / right),
                     Clamp(static_cast<float>(B) / right),
                     Clamp(static_cast<float>(A) / right));
    }

    bool Color::operator == (Color right) const
    {
        return R == right.R && G == right.G && B == right.B && A == right.A;
    }

    bool Color::operator != (Color right) const
    {
        return !operator == (right);
    }
}