#include <Bibim/Config.h>
#include <Bibim/Any.h>
#include <Bibim/BinaryReader.h>
#include <Bibim/BinaryWriter.h>

namespace Bibim
{
    const Any Any::Void;
    const Any Any::True(true);
    const Any Any::False(false);

    Any::Any(const Any& original)
        : type(original.type)
    {
        switch (type)
        {
            case VoidType:
            case BoolType:
            case IntType:
            case LongIntType:
            case FloatType:
            case ColorType:
            case Int2Type:
                value = original.value;
                break;
            case Int3Type:
            case Int4Type:
                value.POINTER = new SixteenBytes(*static_cast<const SixteenBytes*>(original.value.POINTER));
                break;
            case Float2Type:
                value = original.value;
                break;
            case Float3Type:
            case Float4Type:
                value.POINTER = new SixteenBytes(*static_cast<const SixteenBytes*>(original.value.POINTER));
                break;
            case StringType:
                value.POINTER = new String(*static_cast<const String*>(original.value.POINTER));
                break;
            case SharedObjectType:
                value.POINTER = new SharedObjectPtr(*static_cast<const SharedObjectPtr*>(original.value.POINTER));
                break;
            case LightObjectType:
                value = original.value;
                break;
        }
    }

    Any::~Any()
    {
        switch (type)
        {
            case VoidType:
            case BoolType:
            case IntType:
            case LongIntType:
            case FloatType:
            case ColorType:
            case Int2Type:
                break;
            case Int3Type:
            case Int4Type:
                delete static_cast<SixteenBytes*>(value.POINTER);
                break;
            case Float2Type:
                break;
            case Float3Type:
            case Float4Type:
                delete static_cast<SixteenBytes*>(value.POINTER);
                break;
            case StringType:
                delete static_cast<String*>(value.POINTER);
                break;
            case SharedObjectType:
                delete static_cast<SharedObjectPtr*>(value.POINTER);
                break;
            case LightObjectType:
                break;
        }
    }

    bool Any::CastBool() const
    {
        switch (type)
        {
            case BoolType:
                return value.BOOLEAN;
            case IntType:
                return value.INT != 0;
            case LongIntType:
                return value.LONGINT != 0;
            case FloatType:
                return value.FLOAT != 0.0f;
            case SharedObjectType:
                return static_cast<SharedObjectPtr*>(value.POINTER)->GetPointee() != nullptr;
            case LightObjectType:
                return value.POINTER != nullptr;
            default:
                return false;
        }
    }

    int Any::CastInt() const
    {
        switch (type)
        {
            case BoolType:
                return value.BOOLEAN ? 1 : 0;
            case IntType:
                return value.INT;
            case LongIntType:
                return static_cast<int>(value.LONGINT);
            case FloatType:
                return static_cast<int>(value.FLOAT);
            default:
                return 0;
        }
    }

    longint Any::CastLongInt() const
    {
        switch (type)
        {
            case BoolType:
                return value.BOOLEAN ? 1 : 0;
            case IntType:
                return static_cast<longint>(value.INT);
            case LongIntType:
                return value.LONGINT;
            case FloatType:
                return static_cast<longint>(value.FLOAT);
            default:
                return 0;
        }
    }

    float Any::CastFloat() const
    {
        switch (type)
        {
            case BoolType:
                return value.BOOLEAN ? 1.0f : 0.0f;
            case IntType:
                return static_cast<float>(value.INT);
            case LongIntType:
                return static_cast<float>(value.LONGINT);
            case FloatType:
                return value.FLOAT;
            default:
                return 0.0f;
        }
    }

    Color Any::CastColor() const
    {
        switch (type)
        {
            case ColorType:
                return Color(static_cast<unsigned long>(value.INT));
            default:
                return Color(0, 0, 0, 0);
        }
    }

    Point2 Any::CastPoint2() const
    {
        switch (type)
        {
            case Int2Type:
                {
                    const SixteenBytes* data = static_cast<const SixteenBytes*>(value.POINTER);
                    return Point2(data->INT4[0], data->INT4[1]);
                }
            default:
                return Point2::Zero;
        }
    }

    Point3 Any::CastPoint3() const
    {
        switch (type)
        {
            case Int3Type:
                {
                    const SixteenBytes* data = static_cast<const SixteenBytes*>(value.POINTER);
                    return Point3(data->INT4[0], data->INT4[1], data->INT4[2]);
                }
            default:
                return Point3::Zero;
        }
    }

    Point4 Any::CastPoint4() const
    {
        switch (type)
        {
            case Int4Type:
                {
                    const SixteenBytes* data = static_cast<const SixteenBytes*>(value.POINTER);
                    return Point4(data->INT4[0], data->INT4[1], data->INT4[2], data->INT4[3]);
                }
            default:
                return Point4::Zero;
        }
    }

    Vector2 Any::CastVector2() const
    {
        switch (type)
        {
            case Float2Type:
                {
                    const SixteenBytes* data = static_cast<const SixteenBytes*>(value.POINTER);
                    return Vector2(data->FLOAT4[0], data->FLOAT4[1]);
                }
            default:
                return Vector2::Zero;
        }
    }

    Vector3 Any::CastVector3() const
    {
        switch (type)
        {
            case Float3Type:
                {
                    const SixteenBytes* data = static_cast<const SixteenBytes*>(value.POINTER);
                    return Vector3(data->FLOAT4[0], data->FLOAT4[1], data->FLOAT4[2]);
                }
            default:
                return Vector3::Zero;
        }
    }

    Vector4 Any::CastVector4() const
    {
        switch (type)
        {
            case Float4Type:
                {
                    const SixteenBytes* data = static_cast<const SixteenBytes*>(value.POINTER);
                    return Vector4(data->FLOAT4[0], data->FLOAT4[1], data->FLOAT4[2], data->FLOAT4[3]);
                }
            default:
                return Vector4::Zero;
        }
    }

    const String& Any::CastString() const
    {
        switch (type)
        {
            case StringType:
                return *static_cast<const String*>(value.POINTER);
            default:
                return String::Empty;
        }
    }

    SharedObject* Any::CastSharedObject() const
    {
        if (type == SharedObjectType)
            return static_cast<SharedObjectPtr*>(value.POINTER)->GetPointee();
        else
            return nullptr;
    }

    void* Any::CastLightObject() const
    {
        switch (type)
        {
            case LightObjectType:
                return value.POINTER;
            case SharedObjectType:
                return static_cast<SharedObjectPtr*>(value.POINTER)->GetPointee();
            default:
                return nullptr;
        }
    }

    Any& Any::operator = (const Any& right)
    {
        Type  oldType  = type;
        Value oldValue = value;

        type = right.type;
        switch (type)
        {
            case VoidType:
            case BoolType:
            case IntType:
            case LongIntType:
            case FloatType:
            case ColorType:
            case Int2Type:
                value = right.value;
                break;
            case Int3Type:
            case Int4Type:
                value.POINTER = new SixteenBytes(*static_cast<const SixteenBytes*>(right.value.POINTER));
                break;
            case Float2Type:
                value = right.value;
                break;
            case Float3Type:
            case Float4Type:
                value.POINTER = new SixteenBytes(*static_cast<const SixteenBytes*>(right.value.POINTER));
                break;
            case StringType:
                value.POINTER = new String(*static_cast<const String*>(right.value.POINTER));
                break;
            case SharedObjectType:
                value.POINTER = new SharedObjectPtr(*static_cast<const SharedObjectPtr*>(right.value.POINTER));
                break;
            case LightObjectType:
                value.POINTER = right.value.POINTER;
                break;
        }

        switch (oldType)
        {
            case VoidType:
            case BoolType:
            case IntType:
            case LongIntType:
            case FloatType:
            case ColorType:
            case Int2Type:
                break;
            case Int3Type:
            case Int4Type:
                delete static_cast<SixteenBytes*>(oldValue.POINTER);
                break;
            case Float2Type:
                break;
            case Float3Type:
            case Float4Type:
                delete static_cast<SixteenBytes*>(oldValue.POINTER);
                break;
            case StringType:
                delete static_cast<String*>(oldValue.POINTER);
                break;
            case SharedObjectType:
                delete static_cast<SharedObjectPtr*>(oldValue.POINTER);
                break;
            case LightObjectType:
                break;
        }

        return *this;
    }

    bool Any::operator == (const Any& right) const
    {
        if (type != right.type)
            return false;

        switch (type)
        {
            case VoidType:
                return true;
            case BoolType:
                return value.BOOLEAN == right.value.BOOLEAN;
            case IntType:
                return value.INT == right.value.INT;
            case LongIntType:
                return value.LONGINT == right.value.LONGINT;
            case FloatType:
                return value.FLOAT == right.value.FLOAT;
            case ColorType:
                return value.INT == right.value.INT;
            case Int2Type:
                return value.INT2[0] == right.value.INT2[0] &&
                       value.INT2[1] == right.value.INT2[1];
            case Int3Type:
                {
                    const SixteenBytes* a = static_cast<const SixteenBytes*>(value.POINTER);
                    const SixteenBytes* b = static_cast<const SixteenBytes*>(right.value.POINTER);
                    return a->INT4[0] == b->INT4[0] &&
                           a->INT4[1] == b->INT4[1] &&
                           a->INT4[2] == b->INT4[2];
                }
            case Int4Type:
                {
                    const SixteenBytes* a = static_cast<const SixteenBytes*>(value.POINTER);
                    const SixteenBytes* b = static_cast<const SixteenBytes*>(right.value.POINTER);
                    return a->INT4[0] == b->INT4[0] &&
                           a->INT4[1] == b->INT4[1] &&
                           a->INT4[2] == b->INT4[2] &&
                           a->INT4[3] == b->INT4[3];
                }
            case Float2Type:
                return value.FLOAT2[0] == right.value.FLOAT2[0] &&
                       value.FLOAT2[1] == right.value.FLOAT2[1];
            case Float3Type:
                {
                    const SixteenBytes* a = static_cast<const SixteenBytes*>(value.POINTER);
                    const SixteenBytes* b = static_cast<const SixteenBytes*>(right.value.POINTER);
                    return a->FLOAT4[0] == b->FLOAT4[0] &&
                           a->FLOAT4[1] == b->FLOAT4[1] &&
                           a->FLOAT4[2] == b->FLOAT4[2];
                }
            case Float4Type:
                {
                    const SixteenBytes* a = static_cast<const SixteenBytes*>(value.POINTER);
                    const SixteenBytes* b = static_cast<const SixteenBytes*>(right.value.POINTER);
                    return a->FLOAT4[0] == b->FLOAT4[0] &&
                           a->FLOAT4[1] == b->FLOAT4[1] &&
                           a->FLOAT4[2] == b->FLOAT4[2] &&
                           a->FLOAT4[3] == b->FLOAT4[3];
                }
            case StringType:
                return *static_cast<const String*>(value.POINTER) == *static_cast<const String*>(right.value.POINTER);
            case SharedObjectType:
                return *static_cast<const SharedObjectPtr*>(value.POINTER) == *static_cast<const SharedObjectPtr*>(right.value.POINTER);
            case LightObjectType:
                return value.POINTER == right.value.POINTER;
        }

        return false;
    }

    Any Any::ReadFromBytes(const byte* buffer, Type type)
    {
        switch (type)
        {
            case VoidType:
                return Any::Void;
            case BoolType:
                return BinaryReader::ToBool(buffer);
            case IntType:
                return BinaryReader::ToInt(buffer);
            case LongIntType:
                return BinaryReader::ToLongInt(buffer);
            case FloatType:
                return BinaryReader::ToFloat(buffer);
            case ColorType:
                return BinaryReader::ToColor(buffer);
            case Int2Type:
                BBStaticAssert(sizeof(int) == 4);
                return Point2(BinaryReader::ToInt(buffer + 0),
                              BinaryReader::ToInt(buffer + 4));
            case Int3Type:
                BBStaticAssert(sizeof(int) == 4);
                return Point3(BinaryReader::ToInt(buffer + 0),
                              BinaryReader::ToInt(buffer + 4),
                              BinaryReader::ToInt(buffer + 8));
            case Int4Type:
                BBStaticAssert(sizeof(int) == 4);
                return Point4(BinaryReader::ToInt(buffer + 0),
                              BinaryReader::ToInt(buffer + 4),
                              BinaryReader::ToInt(buffer + 8),
                              BinaryReader::ToInt(buffer + 12));
            case Float2Type:
                BBStaticAssert(sizeof(float) == 4);
                return Vector2(BinaryReader::ToFloat(buffer + 0),
                               BinaryReader::ToFloat(buffer + 4));
            case Float3Type:
                BBStaticAssert(sizeof(float) == 4);
                return Vector3(BinaryReader::ToFloat(buffer + 0),
                               BinaryReader::ToFloat(buffer + 4),
                               BinaryReader::ToFloat(buffer + 8));
            case Float4Type:
                BBStaticAssert(sizeof(float) == 4);
                return Vector4(BinaryReader::ToFloat(buffer + 0),
                               BinaryReader::ToFloat(buffer + 4),
                               BinaryReader::ToFloat(buffer + 8),
                               BinaryReader::ToFloat(buffer + 12));
            case StringType:
            case SharedObjectType:
            case LightObjectType:
            default:
                // EXCEPTION
                return Any::Void;
        }
    }

    int Any::WriteToBytes(byte* buffer, const Any& value)
    {
        const SixteenBytes* sixteenBytes = static_cast<const SixteenBytes*>(value.value.POINTER);

        switch (value.type)
        {
            case VoidType:
                return 0;
            case BoolType:
                BinaryWriter::From(buffer, value.value.BOOLEAN);
                return sizeof(value.value.BOOLEAN);
            case IntType:
                BinaryWriter::From(buffer, value.value.INT);
                return sizeof(value.value.INT);
            case LongIntType:
                BinaryWriter::From(buffer, value.value.LONGINT);
                return sizeof(value.value.LONGINT);
            case FloatType:
                BinaryWriter::From(buffer, value.value.FLOAT);
                return sizeof(value.value.FLOAT);
            case ColorType:
                BinaryWriter::From(buffer, value.value.INT);
                return sizeof(value.value.INT);
            case Int2Type:
                BBStaticAssert(sizeof(int) == 4);
                BinaryWriter::From(buffer + 0, value.value.INT2[0]);
                BinaryWriter::From(buffer + 4, value.value.INT2[1]);
                return sizeof(int) * 2;
            case Int3Type:
                BBStaticAssert(sizeof(int) == 4);
                BinaryWriter::From(buffer + 0, sixteenBytes->INT4[0]);
                BinaryWriter::From(buffer + 4, sixteenBytes->INT4[1]);
                BinaryWriter::From(buffer + 8, sixteenBytes->INT4[2]);
                return sizeof(int) * 3;
            case Int4Type:
                BBStaticAssert(sizeof(int) == 4);
                BinaryWriter::From(buffer + 0, sixteenBytes->INT4[0]);
                BinaryWriter::From(buffer + 4, sixteenBytes->INT4[1]);
                BinaryWriter::From(buffer + 8, sixteenBytes->INT4[2]);
                BinaryWriter::From(buffer + 12, sixteenBytes->INT4[3]);
                return sizeof(int) * 4;
            case Float2Type:
                BBStaticAssert(sizeof(float) == 4);
                BinaryWriter::From(buffer + 0, value.value.FLOAT2[0]);
                BinaryWriter::From(buffer + 4, value.value.FLOAT2[1]);
                return sizeof(float) * 2;
            case Float3Type:
                BBStaticAssert(sizeof(float) == 4);
                BinaryWriter::From(buffer + 0, sixteenBytes->FLOAT4[0]);
                BinaryWriter::From(buffer + 4, sixteenBytes->FLOAT4[1]);
                BinaryWriter::From(buffer + 8, sixteenBytes->FLOAT4[2]);
                return sizeof(float) * 3;
            case Float4Type:
                BBStaticAssert(sizeof(float) == 4);
                BinaryWriter::From(buffer + 0, sixteenBytes->FLOAT4[0]);
                BinaryWriter::From(buffer + 4, sixteenBytes->FLOAT4[1]);
                BinaryWriter::From(buffer + 8, sixteenBytes->FLOAT4[2]);
                BinaryWriter::From(buffer + 12, sixteenBytes->FLOAT4[3]);
                return sizeof(float) * 4;
            case StringType:
            case SharedObjectType:
            case LightObjectType:
                // EXCEPTION
                break;
        }

        return 0;
    }

    int Any::WriteToBytes(byte* buffer, const Any& value, Type castType)
    {
        if (value.type == castType)
            return WriteToBytes(buffer, value);
        else
        {
            switch (value.type)
            {
                case VoidType:
                    return 0; // throw;
                case BoolType:
                    switch (castType)
                    {
                        case IntType:
                            BinaryWriter::From(buffer, static_cast<int>(value.value.BOOLEAN ? 1 : 0));
                            return sizeof(int);
                        case LongIntType:
                            BinaryWriter::From(buffer, static_cast<longint>(value.value.BOOLEAN ? 1 : 0));
                            return sizeof(longint);
                        case FloatType:
                            BinaryWriter::From(buffer, static_cast<float>(value.value.BOOLEAN ? 1.0f : 0.0f));
                            return sizeof(float);
                        case StringType:
                            return 0; // throw;
                        default:
                            return 0; // throw;
                    }
                    break;
                case IntType:
                    switch (castType)
                    {
                        case BoolType:
                            BinaryWriter::From(buffer, static_cast<bool>(value.value.INT != 0));
                            return sizeof(bool);
                        case LongIntType:
                            BinaryWriter::From(buffer, static_cast<longint>(value.value.INT));
                            return sizeof(longint);
                        case FloatType:
                            BinaryWriter::From(buffer, static_cast<float>(value.value.INT));
                            return sizeof(float);
                        case StringType:
                            return 0; // throw;
                        default:
                            return 0; // throw;
                    }
                    break;
                case LongIntType:
                    switch (castType)
                    {
                        case BoolType:
                            BinaryWriter::From(buffer, static_cast<bool>(value.value.LONGINT != 0));
                            return sizeof(bool);
                        case IntType:
                            BinaryWriter::From(buffer, static_cast<int>(value.value.LONGINT));
                            return sizeof(int);
                        case FloatType:
                            BinaryWriter::From(buffer, static_cast<float>(value.value.LONGINT));
                            return sizeof(float);
                        case StringType:
                            return 0; // throw;
                        default:
                            return 0; // throw;
                    }
                    break;
                case FloatType:
                    switch (castType)
                    {
                        case BoolType:
                            BinaryWriter::From(buffer, static_cast<bool>(value.value.FLOAT != 0.0f));
                            return sizeof(bool);
                        case IntType:
                            BinaryWriter::From(buffer, static_cast<int>(value.value.FLOAT));
                            return sizeof(int);
                        case LongIntType:
                            BinaryWriter::From(buffer, static_cast<longint>(value.value.FLOAT));
                            return sizeof(longint);
                        case StringType:
                            return 0; // throw;
                        default:
                            return 0; // throw;
                    }
                    break;
                case ColorType:
                    return 0; // throw;
                case Int2Type:
                    return 0; // throw;
                case Int3Type:
                    return 0; // throw;
                case Int4Type:
                    return 0; // throw;
                case Float2Type:
                    return 0; // throw;
                case Float3Type:
                    return 0; // throw;
                case Float4Type:
                    return 0; // throw;
                case StringType:
                    return 0; // throw;
                case SharedObjectType:
                    return 0; // throw;
                case LightObjectType:
                    return 0; // throw;
                default:
                    return 0; // throw;
            }
        }
    }
}