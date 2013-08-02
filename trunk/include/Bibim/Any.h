#pragma once
#ifndef __BIBIM_ANY_H__
#define __BIBIM_ANY_H__

#include <Bibim/FWD.h>
#include <Bibim/Color.h>
#include <Bibim/Point2.h>
#include <Bibim/Point3.h>
#include <Bibim/Point4.h>
#include <Bibim/String.h>
#include <Bibim/Vector2.h>
#include <Bibim/Vector3.h>
#include <Bibim/Vector4.h>

namespace Bibim
{
    /// @brief 여러가지 형식의 값을 보관하는 class.
    ///
    /// C++ 기본 형식(bool, int, ...)과
    /// Bibim 기본 형식(String, Vector2, ...)은 최적화된 형태로 제공됩니다. <br/>
    /// <br/>
    /// SharedObject는 Reference-counting 형태로 올바르게 관리하며
    /// 그 외 객체들은 RawPointer(void*) 형태로 관리합니다. <br/>
    ///
    /// @see boost::any
    /// @see MFC VARIANT
    class Any
    {
        public:
            enum Type
            {
                VoidType,
                BoolType,
                IntType,
                LongIntType,
                FloatType,
                ColorType,
                Int2Type,
                Int3Type,
                Int4Type,
                Float2Type,
                Float3Type,
                Float4Type,
                StringType, // (Bibim::String)
                SharedObjectType,
                LightObjectType, // (void*)
                Point2Type = Int2Type,
                Point3Type = Int3Type,
                Point4Type = Int4Type,
                Vector2Type = Float2Type,
                Vector3Type = Float3Type,
                Vector4Type = Float4Type,
            };

        public:
            inline Any();
            inline Any(bool value);
            inline Any(int value);
            inline Any(longint value);
            inline Any(float value);
            inline Any(Color value);
            inline Any(Point2 value);
            inline Any(Point3 value);
            inline Any(Point4 value);
            inline Any(Vector2 value);
            inline Any(Vector3 value);
            inline Any(Vector4 value);
            inline Any(const char* value);
            inline Any(const String& value);
            inline Any(SharedObject* value);
            inline Any(void* value);
            Any(const Any& original);
            ~Any();

            /// 보관된 값의 형식을 가져옵니다.
            inline Type GetType() const;

            ///@name 보관된 값을 변환하여 반환하는 Methods
            ///@{
                /// @brief 보관된 값을 bool형으로 변환하여 반환합니다.
                ///
                /// select Type <br />
                ///     case Void                       => false <br />
                ///     case Int, LongInt, Float        => 0이면 false, 아니면 true <br />
                ///     case LightObject, SharedObject  => nullptr이면 false, 아니면 true <br/>
                bool CastBool() const;
                /// @brief 보관된 값을 int형으로 변환하여 반환합니다.
                ///
                /// select Type <br/>
                ///     case Void => 0 <br/>
                ///     case Bool => true면 1, false면 0 <br/>
                int CastInt() const;
                /// @brief 보관된 값을 longint형으로 변환하여 반환합니다.
                /// @copydetails Bibim::Any::CastInt
                longint CastLongInt() const;
                /// @brief 보관된 값을 float형으로 변환하여 반환합니다.
                /// @copydetails Bibim::Any::CastInt
                float CastFloat() const;
                /// 보관된 값을 Color형으로 변환하여 반환합니다.
                Color CastColor() const;
                /// 보관된 값을 String형으로 변환하여 반환합니다.
                String CastString() const;
                /// 보관된 값을 SharedObject형으로 변환하여 반환합니다.
                SharedObject* CastSharedObject() const;
                /// 보관된 값을 LightObject형으로 변환하여 반환합니다.
                void* CastLightObject() const;
            ///@}

            ///@name 재정의된 연산자
            ///@{
                Any& operator = (const Any& right);
                bool operator == (const Any& right) const;
                inline bool operator != (const Any& right) const;
            ///@}

            static inline int SizeOf(Type value);

            /// @brief 입력한 buffer부터 값을 읽어와 Any를 생성합니다.
            /// @param buffer 입력 byte 배열 (형식 정보는 따로 담겨있지 않습니다)
            /// @param type   입력 byte 배열에 담긴 값의 형식
            static Any ReadFromBytes(const byte* buffer, Type type);
            /// @brief  Any에 보관된 값을 byte 배열에 기록합니다. 형식 정보 없이 값만 기록합니다.
            /// @param  buffer 출력 byte 배열
            /// @param  value  출력할 값을 담은 객체
            /// @return buffer에 기록한 값의 길이
            static int WriteToBytes(byte* buffer, const Any& value);
            /// @brief Any에 보관된 값을 byte 배열에 
            /// @param buffer   출력 byte 배열
            /// @param value    출력할 값을 담은 객체
            /// @param castType 출력할 형식 (value를 변환합니다)
            /// @return buffer에 기록한 값의 길이
            static int WriteToBytes(byte* buffer, const Any& value, Type castType);

        public:
            static const Any Void;
            static const Any True;
            static const Any False;

        private:
            union Value
            {
                bool    BOOLEAN;
                int     INT;
                longint LONGINT;
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

                explicit Value(int value)
                {
                    INT = value;
                }

                explicit Value(longint value)
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

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    typedef Any::Type AnyType;

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

#endif