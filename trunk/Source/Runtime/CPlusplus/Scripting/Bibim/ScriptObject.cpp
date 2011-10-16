#include <Bibim/ScriptObject.h>
#include <Bibim/BinaryReader.h>
#include <Bibim/BinaryWriter.h>

namespace Bibim
{
    const ScriptObject ScriptObject::Void;

    ScriptObject::ScriptObject(const ScriptObject& original)
        : type(original.type)
    {
        switch (type)
        {
            case VoidType:
            case BoolType:
            case IntType:
            case UIntType:
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

    ScriptObject::~ScriptObject()
    {
        switch (type)
        {
            case VoidType:
            case BoolType:
            case IntType:
            case UIntType:
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

    bool ScriptObject::CastBool() const
    {
        switch (type)
        {
            case BoolType:
                return value.BOOLEAN;
            case IntType:
                return value.INT != 0;
            case UIntType:
                return value.UINT != 0;
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

    int ScriptObject::CastInt() const
    {
        switch (type)
        {
            case BoolType:
                return value.BOOLEAN ? 1 : 0;
            case IntType:
                return value.INT;
            case UIntType:
                return static_cast<int>(value.UINT);
            case LongIntType:
                return static_cast<int>(value.LONGINT);
            case FloatType:
                return static_cast<int>(value.FLOAT);
            default:
                return 0;
        }
    }

    uint ScriptObject::CastUInt() const
    {
        switch (type)
        {
            case BoolType:
                return value.BOOLEAN ? 1 : 0;
            case IntType:
                return static_cast<uint>(value.INT);
            case UIntType:
                return value.UINT;
            case LongIntType:
                return static_cast<uint>(value.LONGINT);
            case FloatType:
                return static_cast<uint>(value.FLOAT);
            default:
                return 0;
        }
    }

    int64 ScriptObject::CastLongInt() const
    {
        switch (type)
        {
            case BoolType:
                return value.BOOLEAN ? 1 : 0;
            case IntType:
                return static_cast<int64>(value.INT);
            case UIntType:
                return static_cast<int64>(value.UINT);
            case LongIntType:
                return value.LONGINT;
            case FloatType:
                return static_cast<int64>(value.FLOAT);
            default:
                return 0;
        }
    }

    float ScriptObject::CastFloat()
    {
        switch (type)
        {
            case BoolType:
                return value.BOOLEAN ? 1.0f : 0.0f;
            case IntType:
                return static_cast<float>(value.INT);
            case UIntType:
                return static_cast<float>(value.UINT);
            case LongIntType:
                return static_cast<float>(value.LONGINT);
            case FloatType:
                return value.FLOAT;
            default:
                return 0.0f;
        }
    }

    SharedObject* ScriptObject::CastSharedObject() const
    {
        if (type == SharedObjectType)
            return static_cast<SharedObjectPtr*>(value.POINTER)->GetPointee();
        else
            return nullptr;
    }

    void* ScriptObject::CastLightObject() const
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

    ScriptObject& ScriptObject::operator = (const ScriptObject& right)
    {
        Type  oldType  = type;
        Value oldValue = value;

        type = right.type;
        switch (type)
        {
            case VoidType:
            case BoolType:
            case IntType:
            case UIntType:
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
            case UIntType:
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

    bool ScriptObject::operator == (const ScriptObject& right) const
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
            case UIntType:
                return value.UINT == right.value.UINT;
            case LongIntType:
                return value.LONGINT == right.value.LONGINT;
            case FloatType:
                return value.FLOAT == right.value.FLOAT;
            case ColorType:
                return value.UINT == right.value.UINT;
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

    ScriptObject ScriptObject::ReadFromBytes(const byte* buffer, Type type)
    {
        switch (type)
        {
            case VoidType:
                return ScriptObject::Void;
            case BoolType:
                return BinaryReader::ToBool(buffer);
            case IntType:
                return BinaryReader::ToInt32(buffer);
            case UIntType:
                return BinaryReader::ToUInt32(buffer);
            case LongIntType:
                return BinaryReader::ToInt64(buffer);
            case FloatType:
                return BinaryReader::ToFloat(buffer);
            case ColorType:
                return BinaryReader::ToColor(buffer);
            case Int2Type:
                // todo
                break;
            case Int3Type:
                // todo
                break;
            case Int4Type:
                // todo
                break;
            case Float2Type:
                BBStaticAssert(sizeof(int) == 4);
                return Vector2(BinaryReader::ToFloat(buffer + 0),
                               BinaryReader::ToFloat(buffer + 4));
            case Float3Type:
                // todo
                break;
            case Float4Type:
                // todo
                break;
            case StringType:
                // todo
                break;
            case SharedObjectType:
                // todo
                break;
            case LightObjectType:
                // todo
                break;
            default:
                return ScriptObject::Void;
        }

        return ScriptObject::Void;
    }

    int ScriptObject::WriteToBytes(byte* buffer, const ScriptObject& value)
    {
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
            case UIntType:
                BinaryWriter::From(buffer, value.value.UINT);
                return sizeof(value.value.UINT);
            case LongIntType:
                BinaryWriter::From(buffer, value.value.LONGINT);
                return sizeof(value.value.LONGINT);
            case FloatType:
                BinaryWriter::From(buffer, value.value.FLOAT);
                return sizeof(value.value.FLOAT);
            case ColorType:
                BinaryWriter::From(buffer, value.value.UINT);
                return sizeof(value.value.UINT);
            case Int2Type:
                BBStaticAssert(sizeof(int) == 4);
                BinaryWriter::From(buffer + 0, value.value.INT2[0]);
                BinaryWriter::From(buffer + 4, value.value.INT2[1]);
                return sizeof(value.value.INT2[0]) + sizeof(value.value.INT2[1]);
            case Int3Type:
                // todo
                break;
            case Int4Type:
                // todo
                break;
            case Float2Type:
                BBStaticAssert(sizeof(float) == 4);
                BinaryWriter::From(buffer + 0, value.value.FLOAT2[0]);
                BinaryWriter::From(buffer + 4, value.value.FLOAT2[1]);
                return sizeof(value.value.FLOAT2[0]) + sizeof(value.value.FLOAT2[1]);
            case Float3Type:
                // todo
                break;
            case Float4Type:
                // todo
                break;
            case StringType:
                // todo
                break;
            case SharedObjectType:
                // todo
                break;
            case LightObjectType:
                // todo
                break;
        }

        return 0;
    }

    int ScriptObject::WriteToBytes(byte* buffer, const ScriptObject& value, Type castType)
    {
        if (value.type == castType)
            return WriteToBytes(buffer, value);
        else
        {
            switch (value.type)
            {
                case VoidType:
                    throw;
                case BoolType:
                    switch (castType)
                    {
                        case IntType:
                            BinaryWriter::From(buffer, static_cast<int>(value.value.BOOLEAN ? 1 : 0));
                            return sizeof(int);
                        case UIntType:
                            BinaryWriter::From(buffer, static_cast<uint>(value.value.BOOLEAN ? 1 : 0));
                            return sizeof(uint);
                        case LongIntType:
                            BinaryWriter::From(buffer, static_cast<int64>(value.value.BOOLEAN ? 1 : 0));
                            return sizeof(int64);
                        case FloatType:
                            BinaryWriter::From(buffer, static_cast<float>(value.value.BOOLEAN ? 1.0f : 0.0f));
                            return sizeof(float);
                        case StringType:
                            throw;
                        default:
                            throw;
                    }
                    break;
                case IntType:
                    switch (castType)
                    {
                        case BoolType:
                            BinaryWriter::From(buffer, static_cast<bool>(value.value.INT != 0));
                            return sizeof(bool);
                        case UIntType:
                            BinaryWriter::From(buffer, static_cast<uint>(value.value.INT));
                            return sizeof(uint);
                        case LongIntType:
                            BinaryWriter::From(buffer, static_cast<int64>(value.value.INT));
                            return sizeof(int64);
                        case FloatType:
                            BinaryWriter::From(buffer, static_cast<float>(value.value.INT));
                            return sizeof(float);
                        case StringType:
                            throw;
                        default:
                            throw;
                    }
                    break;
                case UIntType:
                    switch (castType)
                    {
                        case BoolType:
                            BinaryWriter::From(buffer, static_cast<bool>(value.value.UINT != 0));
                            return sizeof(bool);
                        case IntType:
                            BinaryWriter::From(buffer, static_cast<int>(value.value.UINT));
                            return sizeof(uint);
                        case LongIntType:
                            BinaryWriter::From(buffer, static_cast<int64>(value.value.UINT));
                            return sizeof(int64);
                        case FloatType:
                            BinaryWriter::From(buffer, static_cast<float>(value.value.UINT));
                            return sizeof(float);
                        case StringType:
                            throw;
                        default:
                            throw;
                    }
                    break;
                case LongIntType:
                    throw;
                case FloatType:
                    switch (castType)
                    {
                        case BoolType:
                            BinaryWriter::From(buffer, static_cast<bool>(value.value.FLOAT != 0.0f));
                            return sizeof(bool);
                        case IntType:
                            BinaryWriter::From(buffer, static_cast<int>(value.value.FLOAT));
                            return sizeof(uint);
                        case UIntType:
                            BinaryWriter::From(buffer, static_cast<uint>(value.value.FLOAT));
                            return sizeof(float);
                        case LongIntType:
                            BinaryWriter::From(buffer, static_cast<int64>(value.value.FLOAT));
                            return sizeof(int64);
                        case StringType:
                            throw;
                        default:
                            throw;
                    }
                    break;
                case ColorType:
                    throw;
                case Int2Type:
                    throw;
                case Int3Type:
                    throw;
                case Int4Type:
                    throw;
                case Float2Type:
                    throw;
                case Float3Type:
                    throw;
                case Float4Type:
                    throw;
                case StringType:
                    throw;
                case SharedObjectType:
                    throw;
                case LightObjectType:
                    throw;
                default:
                    throw;
            }
        }
    }
}