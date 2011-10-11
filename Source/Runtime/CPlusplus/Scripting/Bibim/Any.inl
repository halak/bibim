#include <Bibim/Assert.h>
#include <Bibim/Exception.h>

namespace Bibim
{
    Variant::Variant()
        : type(NullType),
          value(nullptr)
    {
    }

    Variant::Variant(MissingTag)
        : type(MissingType),
          value(nullptr)
    {
    }

    Variant::Variant(bool value)
        : type(BoolType),
          value(reinterpret_cast<void*>(value))          
    {
    }

    Variant::Variant(char value)
        : type(CharType),
          value(reinterpret_cast<void*>(value))
    {
    }

    Variant::Variant(unsigned char value)
        : type(UCharType),
          value(reinterpret_cast<void*>(value))
    {
    }

    Variant::Variant(short value)
        : type(ShortType),
          value(reinterpret_cast<void*>(value))
    {
    }

    Variant::Variant(unsigned short value)
        : type(UShortType),
          value(reinterpret_cast<void*>(value))
    {
    }

    Variant::Variant(int value)
        : type(IntType),
          value(reinterpret_cast<void*>(value))
    {
    }

    Variant::Variant(unsigned int value)
        : type(UIntType),
          value(reinterpret_cast<void*>(value))
    {
    }

    Variant::Variant(long value)
        : type(LongType),
          value(reinterpret_cast<void*>(value))
    {
    }

    Variant::Variant(unsigned long value)
        : type(ULongType),
          value(reinterpret_cast<void*>(value))
    {
    }

    Variant::Variant(int64 value)
        : type(Int64Type),
          value(reinterpret_cast<void*>(new SmallStorage<int64>(value)))
    {
    }
    
    Variant::Variant(uint64 value)
        : type(UInt64Type),
          value(reinterpret_cast<void*>(new SmallStorage<uint64>(value)))
    {
    }

    Variant::Variant(float value)
        : type(FloatType),
          value(reinterpret_cast<void*>(new SmallStorage<float>(value)))
    {
    }

    Variant::Variant(double value)
        : type(DoubleType),
          value(reinterpret_cast<void*>(new SmallStorage<double>(value)))
    {
    }

    Variant::Variant(Color value)
        : type(ColorType),
          value(reinterpret_cast<void*>(new SmallStorage<Color>(value)))
    {
    }

    Variant::Variant(const Matrix4& value)
        : type(Matrix4Type),
          value(reinterpret_cast<void*>(new SmallStorage<Matrix4>(value)))
    {
    }

    Variant::Variant(Point value)
        : type(PointType),
          value(reinterpret_cast<void*>(new SmallStorage<Point>(value)))
    {
    }

    Variant::Variant(Quaternion value)
        : type(QuaternionType),
          value(reinterpret_cast<void*>(new SmallStorage<Quaternion>(value)))
    {
    }

    Variant::Variant(Rect value)
        : type(RectType),
          value(reinterpret_cast<void*>(new SmallStorage<Rect>(value)))
    {
    }

    Variant::Variant(RectF value)
        : type(RectFType),
          value(reinterpret_cast<void*>(new SmallStorage<RectF>(value)))
    {
    }

    Variant::Variant(const char* value)
        : type(value ? StringType : NullType),
          value(value ? reinterpret_cast<void*>(new SmallStorage<String>(value)) : nullptr)
    {
    }

    Variant::Variant(const String& value)
        : type(StringType),
          value(reinterpret_cast<void*>(new SmallStorage<String>(value)))
    {
    }

    Variant::Variant(const URI& value)
        : type(URIType),
          value(reinterpret_cast<void*>(new SmallStorage<URI>(value)))
    {
    }

    Variant::Variant(UUID value)
        : type(UUIDType),
          value(reinterpret_cast<void*>(new SmallStorage<UUID>(value)))
    {
    }

    Variant::Variant(Vector2 value)
        : type(Vector2Type),
          value(reinterpret_cast<void*>(new SmallStorage<Vector2>(value)))
    {
    }

    Variant::Variant(Vector3 value)
        : type(Vector3Type),
          value(reinterpret_cast<void*>(new SmallStorage<Vector3>(value)))
    {
    }

    Variant::Variant(Vector4 value)
        : type(Vector4Type),
          value(reinterpret_cast<void*>(new SmallStorage<Vector4>(value)))
    {
    }

    template <typename T> Variant::Variant(const T& value)
        : type(ClassType),
          value(reinterpret_cast<void*>(new ClassStorage<T>(value)))
    {
    }

    template <typename T> Variant::Variant(const T& value, const String& tag)
        : type(ClassType),
          value(reinterpret_cast<void*>(new ClassStorage<T>(value, tag)))
    {
    }

    Variant::Variant(const Variant& original)
        : value(nullptr),
          type(NullType)
    {
        operator = (original);
    }

    Variant::Type Variant::GetType() const
    {
        return type;
    }

    bool Variant::GetBoolean() const
    {
        BBAssertDebug(type == BoolType);
        return reinterpret_cast<bool>(value);
    }

    char Variant::GetChar() const
    {
        BBAssertDebug(type == CharType);
        return reinterpret_cast<char>(value);
    }

    unsigned char Variant::GetUChar() const
    {
        BBAssertDebug(type == UCharType);
        return reinterpret_cast<unsigned char>(value);
    }

    short Variant::GetShort() const
    {
        BBAssertDebug(type == ShortType);
        return reinterpret_cast<short>(value);
    }

    unsigned short Variant::GetUShort() const
    {
        BBAssertDebug(type == UShortType);
        return reinterpret_cast<unsigned short>(value);
    }

    int Variant::GetInt() const
    {
        BBAssertDebug(type == IntType);
        return reinterpret_cast<int>(value);
    }

    unsigned int Variant::GetUInt() const
    {
        BBAssertDebug(type == UIntType);
        return reinterpret_cast<unsigned int>(value);
    }

    long Variant::GetLong() const
    {
        BBAssertDebug(type == LongType);
        return reinterpret_cast<long>(value);
    }

    unsigned long Variant::GetULong() const
    {
        BBAssertDebug(type == ULongType);
        return reinterpret_cast<unsigned long>(value);
    }

    int64 Variant::GetInt64() const
    {
        BBAssertDebug(type == Int64Type);
        return reinterpret_cast<SmallStorage<int64>*>(value)->Value;
    }

    uint64 Variant::GetUInt64() const
    {
        BBAssertDebug(type == UInt64Type);
        return reinterpret_cast<SmallStorage<uint64>*>(value)->Value;
    }

    float Variant::GetFloat() const
    {
        BBAssertDebug(type == FloatType);
        return reinterpret_cast<SmallStorage<float>*>(value)->Value;
    }

    double Variant::GetDouble() const
    {
        BBAssertDebug(type == DoubleType);
        return reinterpret_cast<SmallStorage<double>*>(value)->Value;
    }

    Color Variant::GetColor() const
    {
        BBAssertDebug(type == ColorType);
        return reinterpret_cast<SmallStorage<Color>*>(value)->Value;
    }

    const Matrix4& Variant::GetMatrix4() const
    {
        BBAssertDebug(type == Matrix4Type);
        return reinterpret_cast<SmallStorage<Matrix4>*>(value)->Value;
    }

    Point Variant::GetPoint() const
    {
        BBAssertDebug(type == PointType);
        return reinterpret_cast<SmallStorage<Point>*>(value)->Value;
    }

    Quaternion Variant::GetQuaternion() const
    {
        BBAssertDebug(type == QuaternionType);
        return reinterpret_cast<SmallStorage<Quaternion>*>(value)->Value;
    }

    Rect Variant::GetRect() const
    {
        BBAssertDebug(type == RectType);
        return reinterpret_cast<SmallStorage<Rect>*>(value)->Value;
    }

    RectF Variant::GetRectF() const
    {
        BBAssertDebug(type == RectFType);
        return reinterpret_cast<SmallStorage<RectF>*>(value)->Value;
    }

    const String& Variant::GetString() const
    {
        BBAssertDebug(type == StringType);
        return reinterpret_cast<SmallStorage<String>*>(value)->Value;
    }

    const URI& Variant::GetURI() const
    {
        BBAssertDebug(type == URIType);
        return reinterpret_cast<SmallStorage<URI>*>(value)->Value;
    }

    UUID Variant::GetUUID() const
    {
        BBAssertDebug(type == UUIDType);
        return reinterpret_cast<SmallStorage<UUID>*>(value)->Value;
    }

    Vector2 Variant::GetVector2() const
    {
        BBAssertDebug(type == Vector2Type);
        return reinterpret_cast<SmallStorage<Vector2>*>(value)->Value;
    }

    Vector3 Variant::GetVector3() const
    {
        BBAssertDebug(type == Vector3Type);
        return reinterpret_cast<SmallStorage<Vector3>*>(value)->Value;
    }

    Vector4 Variant::GetVector4() const
    {
        BBAssertDebug(type == Vector4Type);
        return reinterpret_cast<SmallStorage<Vector4>*>(value)->Value;
    }

    template <typename T> T Variant::CastNumericValueTo() const
    {
        switch (type)
        {
            case BoolType:
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

    template <typename T> T Variant::CastTo() const
    {
        if (type == ClassType)
            return *reinterpret_cast<ClassStorage<T>*>(value)->Value;
        else
            BBThrow(BadCastException());
    }

    template <> inline bool Variant::CastTo<bool>() const
    {
        switch (type)
        {
            case NullType:
            case MissingType:
                return false;
            case BoolType:
                return GetBoolean();
            default:
                return true;
        }
    }

    template <> inline char Variant::CastTo<char>() const
    {
        return CastNumericValueTo<char>();
    }

    template <> inline unsigned char Variant::CastTo<unsigned char>() const
    {
        return CastNumericValueTo<unsigned char>();
    }

    template <> inline short Variant::CastTo<short>() const
    {
        return CastNumericValueTo<short>();
    }

    template <> inline unsigned short Variant::CastTo<unsigned short>() const
    {
        return CastNumericValueTo<unsigned short>();
    }

    template <> inline int Variant::CastTo<int>() const
    {
        return CastNumericValueTo<int>();
    }

    template <> inline unsigned int Variant::CastTo<unsigned int>() const
    {
        return CastNumericValueTo<unsigned int>();
    }

    template <> inline long Variant::CastTo<long>() const
    {
        return CastNumericValueTo<long>();
    }

    template <> inline unsigned long Variant::CastTo<unsigned long>() const
    {
        return CastNumericValueTo<unsigned long>();
    }

    template <> inline int64 Variant::CastTo<int64>() const
    {
        return CastNumericValueTo<int64>();
    }

    template <> inline uint64 Variant::CastTo<uint64>() const
    {
        return CastNumericValueTo<uint64>();
    }

    template <> inline float Variant::CastTo<float>() const
    {
        return CastNumericValueTo<float>();
    }

    template <> inline double Variant::CastTo<double>() const
    {
        return CastNumericValueTo<double>();
    }

    template <> inline Color Variant::CastTo<Color>() const
    {
        if (type == ColorType)
            return GetColor();
        else
            BBThrow(BadCastException());
    }

    template <> inline Matrix4 Variant::CastTo<Matrix4>() const
    {
        if (type == Matrix4Type)
            return GetMatrix4();
        else
            BBThrow(BadCastException());
    }

    template <> inline Point Variant::CastTo<Point>() const
    {
        if (type == PointType)
            return GetPoint();
        else
            BBThrow(BadCastException());
    }

    template <> inline Quaternion Variant::CastTo<Quaternion>() const
    {
        if (type == QuaternionType)
            return GetQuaternion();
        else
            BBThrow(BadCastException());
    }

    template <> inline Rect Variant::CastTo<Rect>() const
    {
        if (type == RectType)
            return GetRect();
        else
            BBThrow(BadCastException());
    }

    template <> inline RectF Variant::CastTo<RectF>() const
    {
        if (type == RectFType)
            return GetRectF();
        else
            BBThrow(BadCastException());
    }

    template <> inline String Variant::CastTo<String>() const
    {
        if (type == StringType)
            return GetString();
        else
            BBThrow(BadCastException());
    }

    template <> inline URI Variant::CastTo<URI>() const
    {
        if (type == URIType)
            return GetURI();
        else
            BBThrow(BadCastException());
    }

    template <> inline UUID Variant::CastTo<UUID>() const
    {
        if (type == UUIDType)
            return GetUUID();
        else
            BBThrow(BadCastException());
    }

    template <> inline Vector2 Variant::CastTo<Vector2>() const
    {
        if (type == Vector2Type)
            return GetVector2();
        else
            BBThrow(BadCastException());
    }

    template <> inline Vector3 Variant::CastTo<Vector3>() const
    {
        if (type == Vector3Type)
            return GetVector3();
        else
            BBThrow(BadCastException());
    }

    template <> inline Vector4 Variant::CastTo<Vector4>() const
    {
        if (type == Vector4Type)
            return GetVector4();
        else
            BBThrow(BadCastException());
    }

    bool Variant::operator < (const Variant& right) const
    {
        return value < right.value;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T> Variant::SmallStorage<T>::SmallStorage(T value)
        : Value(value)
    {
    }

    template <typename T> Variant::SmallStorage<T>::SmallStorage(const SmallStorage<T>& original)
        : Value(original.Value)
    {
    }

    template <typename T> Variant::SmallStorage<T>::~SmallStorage()
    {
    }

    template <typename T> Variant::Storage* Variant::SmallStorage<T>::Clone() const
    {
        return new SmallStorage<T>(*this);
    }

    template <typename T> bool Variant::SmallStorage<T>::Equals(const Storage* right) const 
    {
        return Value == static_cast<const SmallStorage<T>*>(right)->Value;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Variant::ClassStorageBase::ClassStorageBase()
    {
    }

    Variant::ClassStorageBase::ClassStorageBase(const String& tag)
        : Tag(tag)
    {
    }

    Variant::ClassStorageBase::ClassStorageBase(const ClassStorageBase& original)
        : Tag(original.Tag)
    {
    }

    Variant::ClassStorageBase::~ClassStorageBase()
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T> Variant::ClassStorage<T>::ClassStorage(const T& value)
        : ClassStorageBase(),
          Value(new T(value))
    {
    }

    template <typename T> Variant::ClassStorage<T>::ClassStorage(const T& value, const String& tag)
        : ClassStorageBase(tag),
          Value(new T(value))
    {
    }

    template <typename T> Variant::ClassStorage<T>::ClassStorage(const ClassStorage<T>& original)
        : ClassStorageBase(original),
          Value(new T(*original.Value))
    {
    }

    template <typename T> Variant::ClassStorage<T>::~ClassStorage()
    {
        delete Value;
    }

    template <typename T> Variant::Storage* Variant::ClassStorage<T>::Clone() const
    {
        return new ClassStorage<T>(*this);
    }

    template <typename T> bool Variant::ClassStorage<T>::Equals(const Storage* right) const
    {
        const ClassStorage<T>* castedRight = static_cast<const ClassStorage<T>*>(right);
        return Tag == castedRight->Tag && (*Value) == (*castedRight->Value);
    }
}