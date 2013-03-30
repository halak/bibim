namespace Bibim
{
    Any::Any()
        : type(VoidType)
    {
    }

    Any::Any(bool value)
        : type(BoolType),
          value(value)
    {
    }

    Any::Any(int value)
        : type(IntType),
          value(value)
    {
    }

    Any::Any(longint value)
        : type(LongIntType),
          value(value)
    {
    }

    Any::Any(float value)
        : type(FloatType),
          value(value)
    {
    }

    Any::Any(Color value)
        : type(ColorType),
          value(static_cast<int>(value.ToARGB()))

    {
    }

    Any::Any(Point2 value)
        : type(Int2Type),
          value(value.X, value.Y)
    {
    }

    Any::Any(Point3 value)
        : type(Int3Type),
          value(new SixteenBytes(value.X, value.Y, value.Z, 0))
    {
    }

    Any::Any(Point4 value)
        : type(Int4Type),
          value(new SixteenBytes(value.X, value.Y, value.Z, value.W))
    {
    }

    Any::Any(Vector2 value)
        : type(Float2Type),
          value(value.X, value.Y)
    {
    }

    Any::Any(Vector3 value)
        : type(Float3Type),
          value(new SixteenBytes(value.X, value.Y, value.Z, 0.0f))
    {
    }

    Any::Any(Vector4 value)
        : type(Float4Type),
          value(new SixteenBytes(value.X, value.Y, value.Z, value.W))
    {
    }

    Any::Any(const char* value)
        : type(StringType),
          value(new String(value))
    {
    }

    Any::Any(const String& value)
        : type(StringType),
          value(new String(value))
    {
    }

    Any::Any(SharedObject* value)
        : type(SharedObjectType),
          value(new SharedObjectPtr(value))
    {
    }

    Any::Any(void* value)
        : type(LightObjectType),
          value(value)
    {
    }

    Any::Type Any::GetType() const
    {
        return type;
    }

    bool Any::operator != (const Any& right) const
    {
        return !operator == (right);
    }

    int Any::SizeOf(Type value)
    {
        switch (value)
        {
            case VoidType:
                return 0;
            case BoolType:
                return sizeof(bool);
            case IntType:
                return sizeof(int);
            case LongIntType:
                return sizeof(longint);
            case FloatType:
                return sizeof(float);
            case ColorType:
                return sizeof(Color);
            case Int2Type:
                return sizeof(int) * 2;
            case Int3Type:
                return sizeof(int) * 3;
            case Int4Type:
                return sizeof(int) * 4;
            case Float2Type:
                return sizeof(float) * 2;
            case Float3Type:
                return sizeof(float) * 3;
            case Float4Type:
                return sizeof(float) * 4;
            case StringType:
                return 0; // throw
            case SharedObjectType:
                return 0; // throw
            case LightObjectType:
                return 0; // throw
            default:
                return 0;
        }
    }
}