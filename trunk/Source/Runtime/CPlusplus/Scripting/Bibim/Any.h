#pragma once
#ifndef __BIBIM_Variant_H__
#define __BIBIM_Variant_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Color.h>
#   include <Bibim/Matrix4.h>
#   include <Bibim/Point.h>
#   include <Bibim/Quaternion.h>
#   include <Bibim/Rect.h>
#   include <Bibim/RectF.h>
#   include <Bibim/String.h>
#   include <Bibim/URI.h>
#   include <Bibim/UUID.h>
#   include <Bibim/Vector2.h>
#   include <Bibim/Vector3.h>
#   include <Bibim/Vector4.h>

    namespace Bibim
    {
        class Variant
        {
            public:
                enum Type
                {
                    NullType,
                    MissingType,

                    BoolType,
                    CharType,
                    UCharType,
                    ShortType,
                    UShortType,
                    IntType,
                    UIntType,
                    LongType,
                    ULongType,
                    Int64Type,
                    UInt64Type,
                    FloatType,
                    DoubleType,

                    ColorType,
                    Matrix4Type,
                    PointType,
                    QuaternionType,
                    RectType,
                    RectFType,
                    StringType,
                    URIType,
                    UUIDType,
                    Vector2Type,
                    Vector3Type,
                    Vector4Type,

                    ClassType,
                };
            
            public:
                inline Variant();
                inline Variant(bool value);
                inline Variant(char value);
                inline Variant(unsigned char value);
                inline Variant(short value);
                inline Variant(unsigned short value);
                inline Variant(int value);
                inline Variant(unsigned int value);
                inline Variant(long value);
                inline Variant(unsigned long value);
                inline Variant(int64 value);
                inline Variant(uint64 value);
                inline Variant(float value);
                inline Variant(double value);
                inline Variant(Color value);
                inline Variant(const Matrix4& value);
                inline Variant(Point value);
                inline Variant(Quaternion value);
                inline Variant(Rect value);
                inline Variant(RectF value);
                inline Variant(const char* value);
                inline Variant(const String& value);
                inline Variant(const URI& value);
                inline Variant(UUID value);
                inline Variant(Vector2 value);
                inline Variant(Vector3 value);
                inline Variant(Vector4 value);
                template <typename T> Variant(const T& value);
                template <typename T> Variant(const T& value, const String& tag);
                inline Variant(const Variant& original);
                ~Variant();

                inline Type GetType() const;
                inline bool GetBoolean() const;
                inline char GetChar() const;
                inline unsigned char GetUChar() const;
                inline short GetShort() const;
                inline unsigned short GetUShort() const;
                inline int GetInt() const;
                inline unsigned int GetUInt() const;
                inline long GetLong() const;
                inline unsigned long GetULong() const;
                inline int64 GetInt64() const;
                inline uint64 GetUInt64() const;
                inline float GetFloat() const;
                inline double GetDouble() const;
                inline Color GetColor() const;
                inline const Matrix4& GetMatrix4() const;
                inline Point GetPoint() const;
                inline Quaternion GetQuaternion() const;
                inline Rect GetRect() const;
                inline RectF GetRectF() const;
                inline const String& GetString() const;
                inline const URI& GetURI() const;
                inline UUID GetUUID() const;
                inline Vector2 GetVector2() const;
                inline Vector3 GetVector3() const;
                inline Vector4 GetVector4() const;
                template <typename T> T CastTo() const;

                // !ONLY! Class
                const String& GetTag() const;

                Variant& operator = (const Variant& right);

                bool operator == (const Variant& right) const;
                bool operator != (const Variant& right) const;

                // std::map에 Key로 쓰이기 위하여 만들어졌습니다.
                inline bool operator < (const Variant& right) const;

            public:
                static const Variant Null;
                static const Variant Missing;

            private:
                struct MissingTag { };
                inline Variant(MissingTag);

                template <typename T> T CastNumericValueTo() const;

            private:
                Type  type;
                void* value;

            private:
                struct Storage
                {
                    virtual ~Storage() { }

                    virtual Storage* Clone() const = 0;
                    virtual bool Equals(const Storage* right) const = 0;
                };

                template <typename T> struct SmallStorage : Storage
                {
                    T Value;

                    SmallStorage(T value);
                    SmallStorage(const SmallStorage<T>& original);
                    virtual ~SmallStorage();

                    virtual Storage* Clone() const;
                    virtual bool Equals(const Storage* right) const;
                };

                struct ClassStorageBase : Storage
                {
                    String Tag;

                    inline ClassStorageBase();
                    inline ClassStorageBase(const String& tag);
                    inline ClassStorageBase(const ClassStorageBase& original);
                    inline virtual ~ClassStorageBase();
                };

                template <typename T> struct ClassStorage : ClassStorageBase
                {
                    T* Value;

                    ClassStorage(const T& value);
                    ClassStorage(const T& value, const String& tag);
                    ClassStorage(const ClassStorage<T>& original);
                    virtual ~ClassStorage();

                    virtual Storage* Clone() const;
                    virtual bool Equals(const Storage* right) const;
                };
        };
    }

#   include <Bibim/Any.inl>

#endif