namespace Bibim
{
    float Math::Atan2(Vector2 xy)
    {
        return Atan2(xy.Y, xy.X);
    }

    char Math::Abs(char value)
    {
        return value >= 0 ? value : -value;
    }

    short Math::Abs(short value)
    {
        return value >= 0 ? value : -value;
    }

    int Math::Abs(int value)
    {
        return value >= 0 ? value : -value;
    }

    long Math::Abs(long value)
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

    char Math::Min(char a, char b)
    {
        return a < b ? a : b;
    }

    uchar Math::Min(uchar a, uchar b)
    {
        return a < b ? a : b;
    }

    short Math::Min(short a, short b)
    {
        return a < b ? a : b;
    }

    ushort Math::Min(ushort a, ushort b)
    {
        return a < b ? a : b;
    }

    int Math::Min(int a, int b)
    {
        return a < b ? a : b;
    }

    uint Math::Min(uint a, uint b)
    {
        return a < b ? a : b;
    }

    long Math::Min(long a, long b)
    {
        return a < b ? a : b;
    }

    ulong Math::Min(ulong a, ulong b)
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

    char Math::Max(char a, char b)
    {
        return a > b ? a : b;
    }

    uchar Math::Max(uchar a, uchar b)
    {
        return a > b ? a : b;
    }

    short Math::Max(short a, short b)
    {
        return a > b ? a : b;
    }

    ushort Math::Max(ushort a, ushort b)
    {
        return a > b ? a : b;
    }

    int Math::Max(int a, int b)
    {
        return a > b ? a : b;
    }

    uint Math::Max(uint a, uint b)
    {
        return a > b ? a : b;
    }

    long Math::Max(long a, long b)
    {
        return a > b ? a : b;
    }

    ulong Math::Max(ulong a, ulong b)
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

    char Math::Min(char a, char b, char c)
    {
        return a < b ? Math::Min(a, c) : Math::Min(b, c);
    }

    uchar Math::Min(uchar a, uchar b, uchar c)
    {
        return a < b ? Math::Min(a, c) : Math::Min(b, c);
    }

    short Math::Min(short a, short b, short c)
    {
        return a < b ? Math::Min(a, c) : Math::Min(b, c);
    }

    ushort Math::Min(ushort a, ushort b, ushort c)
    {
        return a < b ? Math::Min(a, c) : Math::Min(b, c);
    }

    int Math::Min(int a, int b, int c)
    {
        return a < b ? Math::Min(a, c) : Math::Min(b, c);
    }

    uint Math::Min(uint a, uint b, uint c)
    {
        return a < b ? Math::Min(a, c) : Math::Min(b, c);
    }

    long Math::Min(long a, long b, long c)
    {
        return a < b ? Math::Min(a, c) : Math::Min(b, c);
    }

    ulong Math::Min(ulong a, ulong b, ulong c)
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

    char Math::Max(char a, char b, char c)
    {
        return a > b ? Math::Max(a, c) : Math::Max(b, c);
    }

    uchar Math::Max(uchar a, uchar b, uchar c)
    {
        return a > b ? Math::Max(a, c) : Math::Max(b, c);
    }

    short Math::Max(short a, short b, short c)
    {
        return a > b ? Math::Max(a, c) : Math::Max(b, c);
    }

    ushort Math::Max(ushort a, ushort b, ushort c)
    {
        return a > b ? Math::Max(a, c) : Math::Max(b, c);
    }

    int Math::Max(int a, int b, int c)
    {
        return a > b ? Math::Max(a, c) : Math::Max(b, c);
    }

    uint Math::Max(uint a, uint b, uint c)
    {
        return a > b ? Math::Max(a, c) : Math::Max(b, c);
    }

    long Math::Max(long a, long b, long c)
    {
        return a > b ? Math::Max(a, c) : Math::Max(b, c);
    }

    ulong Math::Max(ulong a, ulong b, ulong c)
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

    char Math::Min(char a, char b, char c, char d)
    {
        return a < b ? Math::Min(a, c, d) : Math::Min(b, c, d);
    }

    uchar Math::Min(uchar a, uchar b, uchar c, uchar d)
    {
        return a < b ? Math::Min(a, c, d) : Math::Min(b, c, d);
    }

    short Math::Min(short a, short b, short c, short d)
    {
        return a < b ? Math::Min(a, c, d) : Math::Min(b, c, d);
    }

    ushort Math::Min(ushort a, ushort b, ushort c, ushort d)
    {
        return a < b ? Math::Min(a, c, d) : Math::Min(b, c, d);
    }

    int Math::Min(int a, int b, int c, int d)
    {
        return a < b ? Math::Min(a, c, d) : Math::Min(b, c, d);
    }

    uint Math::Min(uint a, uint b, uint c, uint d)
    {
        return a < b ? Math::Min(a, c, d) : Math::Min(b, c, d);
    }

    long Math::Min(long a, long b, long c, long d)
    {
        return a < b ? Math::Min(a, c, d) : Math::Min(b, c, d);
    }

    ulong Math::Min(ulong a, ulong b, ulong c, ulong d)
    {
        return a < b ? Math::Min(a, c, d) : Math::Min(b, c, d);
    }

    float Math::Min(float a, float b, float c, float d)
    {
        return a < b ? Math::Min(a, c, d) : Math::Min(b, c, d);
    }

    double Math::Min(double a, double b, double c, double d)
    {
        return a < b ? Math::Min(a, c, d) : Math::Min(b, c, d);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    char Math::Max(char a, char b, char c, char d)
    {
        return a > b ? Math::Max(a, c, d) : Math::Max(b, c, d);
    }

    uchar Math::Max(uchar a, uchar b, uchar c, uchar d)
    {
        return a > b ? Math::Max(a, c, d) : Math::Max(b, c, d);
    }

    short Math::Max(short a, short b, short c, short d)
    {
        return a > b ? Math::Max(a, c, d) : Math::Max(b, c, d);
    }

    ushort Math::Max(ushort a, ushort b, ushort c, ushort d)
    {
        return a > b ? Math::Max(a, c, d) : Math::Max(b, c, d);
    }

    int Math::Max(int a, int b, int c, int d)
    {
        return a > b ? Math::Max(a, c, d) : Math::Max(b, c, d);
    }

    uint Math::Max(uint a, uint b, uint c, uint d)
    {
        return a > b ? Math::Max(a, c, d) : Math::Max(b, c, d);
    }

    long Math::Max(long a, long b, long c, long d)
    {
        return a > b ? Math::Max(a, c, d) : Math::Max(b, c, d);
    }

    ulong Math::Max(ulong a, ulong b, ulong c, ulong d)
    {
        return a > b ? Math::Max(a, c, d) : Math::Max(b, c, d);
    }

    float Math::Max(float a, float b, float c, float d)
    {
        return a > b ? Math::Max(a, c, d) : Math::Max(b, c, d);
    }

    double Math::Max(double a, double b, double c, double d)
    {
        return a > b ? Math::Max(a, c, d) : Math::Max(b, c, d);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    char Math::Clamp(char value, char min, char max)
    {
        return value < min ? min : (value > max ? max : value);
    }

    uchar Math::Clamp(uchar value, uchar min, uchar max)
    {
        return value < min ? min : (value > max ? max : value);
    }

    short Math::Clamp(short value, short min, short max)
    {
        return value < min ? min : (value > max ? max : value);
    }

    ushort Math::Clamp(ushort value, ushort min, ushort max)
    {
        return value < min ? min : (value > max ? max : value);
    }

    int Math::Clamp(int value, int min, int max)
    {
        return value < min ? min : (value > max ? max : value);
    }

    uint Math::Clamp(uint value, uint min, uint max)
    {
        return value < min ? min : (value > max ? max : value);
    }

    long Math::Clamp(long value, long min, long max)
    {
        return value < min ? min : (value > max ? max : value);
    }

    ulong Math::Clamp(ulong value, ulong min, ulong max)
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

    int Math::Interpolate(int a, int b, float t)
    {
        return a + static_cast<int>(static_cast<float>(b - a) * t);
    }

    float Math::Interpolate(float a, float b, float t)
    {
        return a + (b - a) * t;
    }

    double Math::Interpolate(double a, double b, float t)
    {
        return a + (b - a) * static_cast<double>(t);
    }

    Point Math::Interpolate(Point a, Point b, float t)
    {
        return Point(Interpolate(a.X, b.X, t),
                     Interpolate(a.Y, b.Y, t));
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