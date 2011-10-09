#pragma once
#ifndef __BIBIM_SCRIPTOBJECT_H__
#define __BIBIM_SCRIPTOBJECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Color.h>
#   include <Bibim/String.h>
#   include <Bibim/Vector2.h>
#   include <Bibim/Vector3.h>
#   include <Bibim/Vector4.h>

    namespace Bibim
    {
        class ScriptObject
        {
            public:
                enum Type
                {
                    VoidType,
                    BooleanType,
                    IntType,
                    UIntType,
                    LongIntType,
                    FloatType,
                    ColorType,
                    Int2Type,
                    Int3Type,
                    Int4Type,
                    Float2Type,
                    Float3Type,
                    Float4Type,
                    StringType,
                    SharedObjectType,
                    LightObjectType,
                    Vector2Type = Float2Type,
                    Vector3Type = Float3Type,
                    Vector4Type = Float4Type,
                };

            public:
                inline ScriptObject();
                inline ScriptObject(bool value);
                inline ScriptObject(int value);
                inline ScriptObject(uint value);
                inline ScriptObject(int64 value);
                inline ScriptObject(float value);
                inline ScriptObject(Color value);
                inline ScriptObject(Vector2 value);
                inline ScriptObject(Vector3 value);
                inline ScriptObject(Vector4 value);
                inline ScriptObject(const char* value);
                inline ScriptObject(const String& value);
                inline ScriptObject(SharedObject* value);
                inline ScriptObject(void* value);
                ScriptObject(const ScriptObject& original);
                ~ScriptObject();

                inline Type GetType() const;

                ScriptObject& operator = (const ScriptObject& right);
                       bool operator == (const ScriptObject& right) const;
                inline bool operator != (const ScriptObject& right) const;

                static inline int SizeOf(Type value);

                static ScriptObject ReadFromBytes(const byte* buffer, Type type);
                static int WriteToBytes(byte* buffer, const ScriptObject& value);
                static int WriteToBytes(byte* buffer, const ScriptObject& value, Type castType);

            public:
                static const ScriptObject Void;

            private:
                union Value
                {
                    bool    BOOLEAN;
                    int     INT;
                    uint    UINT;
                    int64   LONGINT;
                    float   FLOAT;
                    int     INT2[2];
                    float   FLOAT2[2];
                    void*   POINTER;

                    Value()
                    {
                        POINTER = 0;
                    }

                    explicit Value(bool value)
                    {
                        BOOLEAN = value;
                    }

                    Value(int value)
                    {
                        INT = value;
                    }

                    explicit Value(uint value)
                    {
                        UINT = value;
                    }

                    explicit Value(int64 value)
                    {
                        LONGINT = value;
                    }

                    explicit Value(float value)
                    {
                        FLOAT = value;
                    }

                    explicit Value(int value1, int value2)
                    {
                        INT2[0] = value1;
                        INT2[1] = value2;
                    }

                    explicit Value(float value1, float value2)
                    {
                        FLOAT2[0] = value1;
                        FLOAT2[1] = value2;
                    }

                    explicit Value(void* value)
                    {
                        POINTER = value;
                    }
                };

                union SixteenBytes
                {
                    int   INT4[4];
                    float FLOAT4[4];

                    SixteenBytes(int value1, int value2, int value3, int value4)
                    {
                        INT4[0] = value1;
                        INT4[1] = value2;
                        INT4[2] = value3;
                        INT4[3] = value4;
                    }

                    SixteenBytes(float value1, float value2, float value3, float value4)
                    {
                        FLOAT4[0] = value1;
                        FLOAT4[1] = value2;
                        FLOAT4[2] = value3;
                        FLOAT4[3] = value4;
                    }
                };

                Type type;
                Value value;
        };

        typedef ScriptObject::Type ScriptObjectType;
    }

#   include <Bibim/ScriptObject.inl>

#endif