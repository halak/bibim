#pragma once
#ifndef __BIBIM_ANY_H__
#define __BIBIM_ANY_H__

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
        class Any
        {
            public:
                enum Type
                {
                    NullType,
                    MissingType,

                    BooleanType,
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
                inline Any();
                inline Any(bool value);
                inline Any(char value);
                inline Any(unsigned char value);
                inline Any(short value);
                inline Any(unsigned short value);
                inline Any(int value);
                inline Any(unsigned int value);
                inline Any(long value);
                inline Any(unsigned long value);
                inline Any(int64 value);
                inline Any(uint64 value);
                inline Any(float value);
                inline Any(double value);
                inline Any(Color value);
                inline Any(const Matrix4& value);
                inline Any(Point value);
                inline Any(Quaternion value);
                inline Any(Rect value);
                inline Any(RectF value);
                inline Any(const char* value);
                inline Any(const String& value);
                inline Any(const URI& value);
                inline Any(UUID value);
                inline Any(Vector2 value);
                inline Any(Vector3 value);
                inline Any(Vector4 value);
                template <typename T> Any(const T& value);
                template <typename T> Any(const T& value, const String& tag);
                inline Any(const Any& original);
                ~Any();

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

                Any& operator = (const Any& right);

                bool operator == (const Any& right) const;
                bool operator != (const Any& right) const;

                // std::map에 Key로 쓰이기 위하여 만들어졌습니다.
                inline bool operator < (const Any& right) const;

            public:
                static const Any Null;
                static const Any Missing;

            private:
                struct MissingTag { };
                inline Any(MissingTag);

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