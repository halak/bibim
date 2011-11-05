namespace Bibim
{
    float Math::Atan2(Vector2 xy)
    {
        return Atan2(xy.Y, xy.X);
    }

    short Math::Abs(short value)
    {
        return value >= 0 ? value : -value;
    }

    int Math::Abs(int value)
    {
        return value >= 0 ? value : -value;
    }

    longint Math::Abs(longint value)
    {
        return value >= 0 ? value : -value;
    }

    float Math::Abs(float value)
    {
        return value >= 0.0f ? value : -value;
    }

    double Math::Abs(double value)
    {
        return value >= 0.0 ? value : -value;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    byte Math::Min(byte a, byte b)
    {
        return a < b ? a : b;
    }

    short Math::Min(short a, short b)
    {
        return a < b ? a : b;
    }

    int Math::Min(int a, int b)
    {
        return a < b ? a : b;
    }

    longint Math::Min(longint a, longint b)
    {
        return a < b ? a : b;
    }

    float Math::Min(float a, float b)
    {
        return a < b ? a : b;
    }

    double Math::Min(double a, double b)
    {
        return a < b ? a : b;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    byte Math::Max(byte a, byte b)
    {
        return a > b ? a : b;
    }

    short Math::Max(short a, short b)
    {
        return a > b ? a : b;
    }

    int Math::Max(int a, int b)
    {
        return a > b ? a : b;
    }

    longint Math::Max(longint a, longint b)
    {
        return a > b ? a : b;
    }

    float Math::Max(float a, float b)
    {
        return a > b ? a : b;
    }

    double Math::Max(double a, double b)
    {
        return a > b ? a : b;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    byte Math::Min(byte a, byte b, byte c)
    {
        return a < b ? Math::Min(a, c) : Math::Min(b, c);
    }

    short Math::Min(short a, short b, short c)
    {
        return a < b ? Math::Min(a, c) : Math::Min(b, c);
    }

    int Math::Min(int a, int b, int c)
    {
        return a < b ? Math::Min(a, c) : Math::Min(b, c);
    }

    longint Math::Min(longint a, longint b, longint c)
    {
        return a < b ? Math::Min(a, c) : Math::Min(b, c);
    }

    float Math::Min(float a, float b, float c)
    {
        return a < b ? Math::Min(a, c) : Math::Min(b, c);
    }

    double Math::Min(double a, double b, double c)
    {
        return a < b ? Math::Min(a, c) : Math::Min(b, c);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    byte Math::Max(byte a, byte b, byte c)
    {
        return a > b ? Math::Max(a, c) : Math::Max(b, c);
    }

    short Math::Max(short a, short b, short c)
    {
        return a > b ? Math::Max(a, c) : Math::Max(b, c);
    }

    int Math::Max(int a, int b, int c)
    {
        return a > b ? Math::Max(a, c) : Math::Max(b, c);
    }

    longint Math::Max(longint a, longint b, longint c)
    {
        return a > b ? Math::Max(a, c) : Math::Max(b, c);
    }

    float Math::Max(float a, float b, float c)
    {
        return a > b ? Math::Max(a, c) : Math::Max(b, c);
    }

    double Math::Max(double a, double b, double c)
    {
        return a > b ? Math::Max(a, c) : Math::Max(b, c);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    byte Math::Clamp(byte value, byte min, byte max)
    {
        return value < min ? min : (value > max ? max : value);
    }

    short Math::Clamp(short value, short min, short max)
    {
        return value < min ? min : (value > max ? max : value);
    }

    int Math::Clamp(int value, int min, int max)
    {
        return value < min ? min : (value > max ? max : value);
    }

    longint Math::Clamp(longint value, longint min, longint max)
    {
        return value < min ? min : (value > max ? max : value);
    }

    float Math::Clamp(float value, float min, float max)
    {
        return value < min ? min : (value > max ? max : value);
    }

    double Math::Clamp(double value, double min, double max)
    {
        return value < min ? min : (value > max ? max : value);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    int Math::Wrap(int value, int upper)
    {
        return (value >= 0) ? value % upper : (upper - ((-value) % upper)) % upper;   
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    short Math::Interpolate(short a, short b, float t)
    {
        return a + static_cast<short>(static_cast<float>(b - a) * t);
    }

    int Math::Interpolate(int a, int b, float t)
    {
        return a + static_cast<int>(static_cast<float>(b - a) * t);
    }

    longint Math::Interpolate(longint a, longint b, float t)
    {
        return a + static_cast<longint>(static_cast<double>(b - a) * t);
    }

    float Math::Interpolate(float a, float b, float t)
    {
        return a + (b - a) * t;
    }

    double Math::Interpolate(double a, double b, float t)
    {
        return a + (b - a) * static_cast<double>(t);
    }

    Point2 Math::Interpolate(Point2 a, Point2 b, float t)
    {
        return Point2(Interpolate(a.X, b.X, t),
                      Interpolate(a.Y, b.Y, t));
    }

    Point3 Math::Interpolate(Point3 a, Point3 b, float t)
    {
        return Point3(Interpolate(a.X, b.X, t),
                      Interpolate(a.Y, b.Y, t),
                      Interpolate(a.Z, b.Z, t));
    }

    Point4 Math::Interpolate(Point4 a, Point4 b, float t)
    {
        return Point4(Interpolate(a.X, b.X, t),
                      Interpolate(a.Y, b.Y, t),
                      Interpolate(a.Z, b.Z, t),
                      Interpolate(a.W, b.W, t));
    }

    Rect Math::Interpolate(Rect a, Rect b, float t)
    {
        return Rect(Interpolate(a.X, b.X, t),
                    Interpolate(a.Y, b.Y, t),
                    Interpolate(a.Width , b.Width,  t),
                    Interpolate(a.Height, b.Height, t));
    }

    RectF Math::Interpolate(RectF a, RectF b, float t)
    {
        return RectF(Interpolate(a.X, b.X, t),
                     Interpolate(a.Y, b.Y, t),
                     Interpolate(a.Width,  b.Width,  t),
                     Interpolate(a.Height, b.Height, t));
    }

    Vector2 Math::Interpolate(Vector2 a, Vector2 b, float t)
    {
        return Vector2(Interpolate(a.X, b.X, t),
                       Interpolate(a.Y, b.Y, t));
    }

    Vector3 Math::Interpolate(Vector3 a, Vector3 b, float t)
    {
        return Vector3(Interpolate(a.X, b.X, t),
                       Interpolate(a.Y, b.Y, t),
                       Interpolate(a.Z, b.Z, t));
    }

    Vector4 Math::Interpolate(Vector4 a, Vector4 b, float t)
    {
        return Vector4(Interpolate(a.X, b.X, t),
                       Interpolate(a.Y, b.Y, t),
                       Interpolate(a.Z, b.Z, t),
                       Interpolate(a.W, b.W, t));
    }

    Color Math::Interpolate(Color a, Color b, float t)
    {
        return Color(Interpolate(static_cast<int>(a.R), static_cast<int>(b.R), t),
                     Interpolate(static_cast<int>(a.G), static_cast<int>(b.G), t),
                     Interpolate(static_cast<int>(a.B), static_cast<int>(b.B), t),
                     Interpolate(static_cast<int>(a.A), static_cast<int>(b.A), t));
    }
}