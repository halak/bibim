#include <Bibim/PCH.h>
#include <Bibim/Any.h>

namespace Bibim
{
    const Variant Variant::Null = Variant();
    const Variant Variant::Missing = Variant(Variant::MissingTag());

    Variant::~Variant()
    {
        switch (type)
        {
            case Int64Type:
            case UInt64Type:
            case FloatType:
            case DoubleType:
            case ColorType:
            case Matrix4Type:
            case PointType:
            case QuaternionType:
            case RectType:
            case RectFType:
            case StringType:
            case URIType:
            case UUIDType:
            case Vector2Type:
            case Vector3Type:
            case Vector4Type:
            case ClassType:
                delete reinterpret_cast<Storage*>(value);
                break;
        }
    }

    const String& Variant::GetTag() const
    {
        if (type == ClassType)
            return reinterpret_cast<ClassStorageBase*>(value)->Tag;
        else
            return String::Empty;
    }

    Variant& Variant::operator = (const Variant& right)
    {
        Type  oldType  = type;
        void* oldValue = value;

        type  = right.type;
        value = nullptr;

        switch (oldType)
        {
            case Int64Type:
            case UInt64Type:
            case FloatType:
            case DoubleType:
            case ColorType:
            case Matrix4Type:
            case PointType:
            case QuaternionType:
            case RectType:
            case RectFType:
            case StringType:
            case URIType:
            case UUIDType:
            case Vector2Type:
            case Vector3Type:
            case Vector4Type:
            case ClassType:
                delete reinterpret_cast<Storage*>(oldValue);
                break;
        }

        switch (type)
        {
            case NullType:
            case MissingType:
                value = nullptr;
                break;
            case BoolType:
            case CharType:
            case UCharType:
            case ShortType:
            case UShortType:
            case IntType:
            case UIntType:
            case LongType:
            case ULongType:
                value = right.value;
                break;
            case Int64Type:
            case UInt64Type:
            case FloatType:
            case DoubleType:
            case ColorType:
            case Matrix4Type:
            case PointType:
            case QuaternionType:
            case RectType:
            case RectFType:
            case StringType:
            case URIType:
            case UUIDType:
            case Vector2Type:
            case Vector3Type:
            case Vector4Type:
            case ClassType:
                value = reinterpret_cast<void*>(reinterpret_cast<Storage*>(right.value)->Clone());
                break;
        }

        return *this;
    }

    bool Variant::operator == (const Variant& right) const
    {
        if (type != right.type)
            return false;

        switch (type)
        {
            case NullType:
            case MissingType:
                return true;
            case BoolType:
            case CharType:
            case UCharType:
            case ShortType:
            case UShortType:
            case IntType:
            case UIntType:
            case LongType:
            case ULongType:
                return value == right.value;
            case Int64Type:
            case UInt64Type:
            case FloatType:
            case DoubleType:
            case ColorType:
            case Matrix4Type:
            case PointType:
            case QuaternionType:
            case RectType:
            case RectFType:
            case StringType:
            case URIType:
            case UUIDType:
            case Vector2Type:
            case Vector3Type:
            case Vector4Type:
            case ClassType:
                return reinterpret_cast<Storage*>(value)->Equals(reinterpret_cast<Storage*>(right.value));
            default:
                return false;
        }
    }

    bool Variant::operator != (const Variant& right) const
    {
        return !operator == (right);
    }
}