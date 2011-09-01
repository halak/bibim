#include <Bibim/Assert.h>
#include <Bibim/Exception.h>

namespace Bibim
{
    Any::Any()
        : type(NullType),
          value(nullptr)
    {
    }

    Any::Any(MissingTag)
        : type(MissingType),
          value(nullptr)
    {
    }

    Any::Any(bool value)
        : type(BooleanType),
          value(reinterpret_cast<void*>(value))          
    {
    }

    Any::Any(char value)
        : type(CharType),
          value(reinterpret_cast<void*>(value))
    {
    }

    Any::Any(unsigned char value)
        : type(UCharType),
          value(reinterpret_cast<void*>(value))
    {
    }

    Any::Any(short value)
        : type(ShortType),
          value(reinterpret_cast<void*>(value))
    {
    }

    Any::Any(unsigned short value)
        : type(UShortType),
          value(reinterpret_cast<void*>(value))
    {
    }

    Any::Any(int value)
        : type(IntType),
          value(reinterpret_cast<void*>(value))
    {
    }

    Any::Any(unsigned int value)
        : type(UIntType),
          value(reinterpret_cast<void*>(value))
    {
    }

    Any::Any(long value)
        : type(LongType),
          value(reinterpret_cast<void*>(value))
    {
    }

    Any::Any(unsigned long value)
        : type(ULongType),
          value(reinterpret_cast<void*>(value))
    {
    }

    Any::Any(int64 value)
        : type(Int64Type),
          value(reinterpret_cast<void*>(new SmallStorage<int64>(value)))
    {
    }
    
    Any::Any(uint64 value)
        : type(UInt64Type),
          value(reinterpret_cast<void*>(new SmallStorage<uint64>(value)))
    {
    }

    Any::Any(float value)
        : type(FloatType),
          value(reinterpret_cast<void*>(new SmallStorage<float>(value)))
    {
    }

    Any::Any(double value)
        : type(DoubleType),
          value(reinterpret_cast<void*>(new SmallStorage<double>(value)))
    {
    }

    Any::Any(Color value)
        : type(ColorType),
          value(reinterpret_cast<void*>(new SmallStorage<Color>(value)))
    {
    }

    Any::Any(const Matrix4& value)
        : type(Matrix4Type),
          value(reinterpret_cast<void*>(new SmallStorage<Matrix4>(value)))
    {
    }

    Any::Any(Point value)
        : type(PointType),
          value(reinterpret_cast<void*>(new SmallStorage<Point>(value)))
    {
    }

    Any::Any(Quaternion value)
        : type(QuaternionType),
          value(reinterpret_cast<void*>(new SmallStorage<Quaternion>(value)))
    {
    }

    Any::Any(Rectangle value)
        : type(RectangleType),
          value(reinterpret_cast<void*>(new SmallStorage<Rectangle>(value)))
    {
    }

    Any::Any(RectangleF value)
        : type(RectangleFType),
          value(reinterpret_cast<void*>(new SmallStorage<RectangleF>(value)))
    {
    }

    Any::Any(const char* value)
        : type(value ? StringType : NullType),
          value(value ? reinterpret_cast<void*>(new SmallStorage<String>(value)) : nullptr)
    {
    }

    Any::Any(const String& value)
        : type(StringType),
          value(reinterpret_cast<void*>(new SmallStorage<String>(value)))
    {
    }

    Any::Any(const URI& value)
        : type(URIType),
          value(reinterpret_cast<void*>(new SmallStorage<URI>(value)))
    {
    }

    Any::Any(UUID value)
        : type(UUIDType),
          value(reinterpret_cast<void*>(new SmallStorage<UUID>(value)))
    {
    }

    Any::Any(Vector2 value)
        : type(Vector2Type),
          value(reinterpret_cast<void*>(new SmallStorage<Vector2>(value)))
    {
    }

    Any::Any(Vector3 value)
        : type(Vector3Type),
          value(reinterpret_cast<void*>(new SmallStorage<Vector3>(value)))
    {
    }

    Any::Any(Vector4 value)
        : type(Vector4Type),
          value(reinterpret_cast<void*>(new SmallStorage<Vector4>(value)))
    {
    }

    template <typename T> Any::Any(const T& value)
        : type(ClassType),
          value(reinterpret_cast<void*>(new ClassStorage<T>(value)))
    {
    }

    template <typename T> Any::Any(const T& value, const String& tag)
        : type(ClassType),
          value(reinterpret_cast<void*>(new ClassStorage<T>(value, tag)))
    {
    }

    Any::Any(const Any& original)
        : value(nullptr),
          type(NullType)
    {
        operator = (original);
    }

    Any::Type Any::GetType() const
    {
        return type;
    }

    bool Any::GetBoolean() const
    {
        BBAssertDebug(type == BooleanType);
        return reinterpret_cast<bool>(value);
    }

    char Any::GetChar() const
    {
        BBAssertDebug(type == CharType);
        return reinterpret_cast<char>(value);
    }

    unsigned char Any::GetUChar() const
    {
        BBAssertDebug(type == UCharType);
        return reinterpret_cast<unsigned char>(value);
    }

    short Any::GetShort() const
    {
        BBAssertDebug(type == ShortType);
        return reinterpret_cast<short>(value);
    }

    unsigned short Any::GetUShort() const
    {
        BBAssertDebug(type == UShortType);
        return reinterpret_cast<unsigned short>(value);
    }

    int Any::GetInt() const
    {
        BBAssertDebug(type == IntType);
        return reinterpret_cast<int>(value);
    }

    unsigned int Any::GetUInt() const
    {
        BBAssertDebug(type == UIntType);
        return reinterpret_cast<unsigned int>(value);
    }

    long Any::GetLong() const
    {
        BBAssertDebug(type == LongType);
        return reinterpret_cast<long>(value);
    }

    unsigned long Any::GetULong() const
    {
        BBAssertDebug(type == ULongType);
        return reinterpret_cast<unsigned long>(value);
    }

    int64 Any::GetInt64() const
    {
        BBAssertDebug(type == Int64Type);
        return reinterpret_cast<SmallStorage<int64>*>(value)->Value;
    }

    uint64 Any::GetUInt64() const
    {
        BBAssertDebug(type == UInt64Type);
        return reinterpret_cast<SmallStorage<uint64>*>(value)->Value;
    }

    float Any::GetFloat() const
    {
        BBAssertDebug(type == FloatType);
        return reinterpret_cast<SmallStorage<float>*>(value)->Value;
    }

    double Any::GetDouble() const
    {
        BBAssertDebug(type == DoubleType);
        return reinterpret_cast<SmallStorage<double>*>(value)->Value;
    }

    Color Any::GetColor() const
    {
        BBAssertDebug(type == ColorType);
        return reinterpret_cast<SmallStorage<Color>*>(value)->Value;
    }

    const Matrix4& Any::GetMatrix4() const
    {
        BBAssertDebug(type == Matrix4Type);
        return reinterpret_cast<SmallStorage<Matrix4>*>(value)->Value;
    }

    Point Any::GetPoint() const
    {
        BBAssertDebug(type == PointType);
        return reinterpret_cast<SmallStorage<Point>*>(value)->Value;
    }

    Quaternion Any::GetQuaternion() const
    {
        BBAssertDebug(type == QuaternionType);
        return reinterpret_cast<SmallStorage<Quaternion>*>(value)->Value;
    }

    Rectangle Any::GetRectangle() const
    {
        BBAssertDebug(type == RectangleType);
        return reinterpret_cast<SmallStorage<Rectangle>*>(value)->Value;
    }

    RectangleF Any::GetRectangleF() const
    {
        BBAssertDebug(type == RectangleFType);
        return reinterpret_cast<SmallStorage<RectangleF>*>(value)->Value;
    }

    const String& Any::GetString() const
    {
        BBAssertDebug(type == StringType);
        return reinterpret_cast<SmallStorage<String>*>(value)->Value;
    }

    const URI& Any::GetURI() const
    {
        BBAssertDebug(type == URIType);
        return reinterpret_cast<SmallStorage<URI>*>(value)->Value;
    }

    UUID Any::GetUUID() const
    {
        BBAssertDebug(type == UUIDType);
        return reinterpret_cast<SmallStorage<UUID>*>(value)->Value;
    }

    Vector2 Any::GetVector2() const
    {
        BBAssertDebug(type == Vector2Type);
        return reinterpret_cast<SmallStorage<Vector2>*>(value)->Value;
    }

    Vector3 Any::GetVector3() const
    {
        BBAssertDebug(type == Vector3Type);
        return reinterpret_cast<SmallStorage<Vector3>*>(value)->Value;
    }

    Vector4 Any::GetVector4() const
    {
        BBAssertDebug(type == Vector4Type);
        return reinterpret_cast<SmallStorage<Vector4>*>(value)->Value;
    }

    template <typename T> T Any::CastNumericValueTo() const
    {
        switch (type)
        {
            case BooleanType:
                return static_cast<T>(GetBoolean());
            case CharType:
                return static_cast<T>(GetChar());
            case UCharType:
                return static_cast<T>(GetUChar());
            case ShortType:
                return static_cast<T>(GetShort());
            case UShortType:
                return static_cast<T>(GetUShort());
            case IntType:
                return static_cast<T>(GetInt());
            case UIntType:
                return static_cast<T>(GetUInt());
            case LongType:
                return static_cast<T>(GetLong());
            case ULongType:
                return static_cast<T>(GetULong());
            case Int64Type:
                return static_cast<T>(GetInt64());
            case UInt64Type:
                return static_cast<T>(GetUInt64());
            case FloatType:
                return static_cast<T>(GetFloat());
            case DoubleType:
                return static_cast<T>(GetDouble());
            default:
                BBThrow(BadCastException());
        }
    }

    template <typename T> T Any::CastTo() const
    {
        if (type == ClassType)
            return *reinterpret_cast<ClassStorage<T>*>(value)->Value;
        else
            BBThrow(BadCastException());
    }

    template <> inline bool Any::CastTo<bool>() const
    {
        switch (type)
        {
            case NullType:
            case MissingType:
                return false;
            case BooleanType:
                return GetBoolean();
            default:
                return true;
        }
    }

    template <> inline char Any::CastTo<char>() const
    {
        return CastNumericValueTo<char>();
    }

    template <> inline unsigned char Any::CastTo<unsigned char>() const
    {
        return CastNumericValueTo<unsigned char>();
    }

    template <> inline short Any::CastTo<short>() const
    {
        return CastNumericValueTo<short>();
    }

    template <> inline unsigned short Any::CastTo<unsigned short>() const
    {
        return CastNumericValueTo<unsigned short>();
    }

    template <> inline int Any::CastTo<int>() const
    {
        return CastNumericValueTo<int>();
    }

    template <> inline unsigned int Any::CastTo<unsigned int>() const
    {
        return CastNumericValueTo<unsigned int>();
    }

    template <> inline long Any::CastTo<long>() const
    {
        return CastNumericValueTo<long>();
    }

    template <> inline unsigned long Any::CastTo<unsigned long>() const
    {
        return CastNumericValueTo<unsigned long>();
    }

    template <> inline int64 Any::CastTo<int64>() const
    {
        return CastNumericValueTo<int64>();
    }

    template <> inline uint64 Any::CastTo<uint64>() const
    {
        return CastNumericValueTo<uint64>();
    }

    template <> inline float Any::CastTo<float>() const
    {
        return CastNumericValueTo<float>();
    }

    template <> inline double Any::CastTo<double>() const
    {
        return CastNumericValueTo<double>();
    }

    template <> inline Color Any::CastTo<Color>() const
    {
        if (type == ColorType)
            return GetColor();
        else
            BBThrow(BadCastException());
    }

    template <> inline Matrix4 Any::CastTo<Matrix4>() const
    {
        if (type == Matrix4Type)
            return GetMatrix4();
        else
            BBThrow(BadCastException());
    }

    template <> inline Point Any::CastTo<Point>() const
    {
        if (type == PointType)
            return GetPoint();
        else
            BBThrow(BadCastException());
    }

    template <> inline Quaternion Any::CastTo<Quaternion>() const
    {
        if (type == QuaternionType)
            return GetQuaternion();
        else
            BBThrow(BadCastException());
    }

    template <> inline Rectangle Any::CastTo<Rectangle>() const
    {
        if (type == RectangleType)
            return GetRectangle();
        else
            BBThrow(BadCastException());
    }

    template <> inline RectangleF Any::CastTo<RectangleF>() const
    {
        if (type == RectangleFType)
            return GetRectangleF();
        else
            BBThrow(BadCastException());
    }

    template <> inline String Any::CastTo<String>() const
    {
        if (type == StringType)
            return GetString();
        else
            BBThrow(BadCastException());
    }

    template <> inline URI Any::CastTo<URI>() const
    {
        if (type == URIType)
            return GetURI();
        else
            BBThrow(BadCastException());
    }

    template <> inline UUID Any::CastTo<UUID>() const
    {
        if (type == UUIDType)
            return GetUUID();
        else
            BBThrow(BadCastException());
    }

    template <> inline Vector2 Any::CastTo<Vector2>() const
    {
        if (type == Vector2Type)
            return GetVector2();
        else
            BBThrow(BadCastException());
    }

    template <> inline Vector3 Any::CastTo<Vector3>() const
    {
        if (type == Vector3Type)
            return GetVector3();
        else
            BBThrow(BadCastException());
    }

    template <> inline Vector4 Any::CastTo<Vector4>() const
    {
        if (type == Vector4Type)
            return GetVector4();
        else
            BBThrow(BadCastException());
    }

    bool Any::operator < (const Any& right) const
    {
        return value < right.value;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T> Any::SmallStorage<T>::SmallStorage(T value)
        : Value(value)
    {
    }

    template <typename T> Any::SmallStorage<T>::SmallStorage(const SmallStorage<T>& original)
        : Value(original.Value)
    {
    }

    template <typename T> Any::SmallStorage<T>::~SmallStorage()
    {
    }

    template <typename T> Any::Storage* Any::SmallStorage<T>::Clone() const
    {
        return new SmallStorage<T>(*this);
    }

    template <typename T> bool Any::SmallStorage<T>::Equals(const Storage* right) const 
    {
        return Value == static_cast<const SmallStorage<T>*>(right)->Value;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Any::ClassStorageBase::ClassStorageBase()
    {
    }

    Any::ClassStorageBase::ClassStorageBase(const String& tag)
        : Tag(tag)
    {
    }

    Any::ClassStorageBase::ClassStorageBase(const ClassStorageBase& original)
        : Tag(original.Tag)
    {
    }

    Any::ClassStorageBase::~ClassStorageBase()
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T> Any::ClassStorage<T>::ClassStorage(const T& value)
        : ClassStorageBase(),
          Value(new T(value))
    {
    }

    template <typename T> Any::ClassStorage<T>::ClassStorage(const T& value, const String& tag)
        : ClassStorageBase(tag),
          Value(new T(value))
    {
    }

    template <typename T> Any::ClassStorage<T>::ClassStorage(const ClassStorage<T>& original)
        : ClassStorageBase(original),
          Value(new T(*original.Value))
    {
    }

    template <typename T> Any::ClassStorage<T>::~ClassStorage()
    {
        delete Value;
    }

    template <typename T> Any::Storage* Any::ClassStorage<T>::Clone() const
    {
        return new ClassStorage<T>(*this);
    }

    template <typename T> bool Any::ClassStorage<T>::Equals(const Storage* right) const
    {
        const ClassStorage<T>* castedRight = static_cast<const ClassStorage<T>*>(right);
        return Tag == castedRight->Tag && (*Value) == (*castedRight->Value);
    }
}