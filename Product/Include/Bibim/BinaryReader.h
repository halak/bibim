#pragma once
#ifndef __BIBIM_STREAMREADER_H__
#define __BIBIM_STREAMREADER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Color.h>
#   include <Bibim/Point2.h>
#   include <Bibim/Point3.h>
#   include <Bibim/Point4.h>
#   include <Bibim/Rect.h>
#   include <Bibim/RectF.h>
#   include <Bibim/String.h>
#   include <Bibim/Vector2.h>
#   include <Bibim/Vector3.h>
#   include <Bibim/Vector4.h>

    namespace Bibim
    {
        class BinaryReader
        {
            public:
                explicit BinaryReader(Stream* sourceStream);
                BinaryReader(const BinaryReader& original);
                ~BinaryReader();

                void*   Read(void* buffer, int length);
                bool    ReadBool();
                byte    ReadByte();
                short   ReadShortInt();
                int     ReadInt();
                longint ReadLongInt();
                float   ReadFloat();
                double  ReadDouble();
                String  ReadString();
                Color   ReadColor();
                Point2  ReadPoint2();
                Point3  ReadPoint3();
                Point4  ReadPoint4();
                Rect    ReadRect();
                RectF   ReadRectF();
                Vector2 ReadVector2();
                Vector3 ReadVector3();
                Vector4 ReadVector4();

                inline void Read(bool& outValue);
                inline void Read(byte& outValue);
                inline void Read(short& outValue);
                inline void Read(int& outValue);
                inline void Read(longint& outValue);
                inline void Read(float& outValue);
                inline void Read(double& outValue);
                inline void Read(String& outValue);
                inline void Read(Color& outValue);
                inline void Read(Point2& outValue);
                inline void Read(Point3& outValue);
                inline void Read(Point4& outValue);
                inline void Read(Rect& outValue);
                inline void Read(RectF& outValue);
                inline void Read(Vector2& outValue);
                inline void Read(Vector3& outValue);
                inline void Read(Vector4& outValue);

                inline Stream* GetSource() const;

                BinaryReader& operator = (const BinaryReader& right);
                inline bool operator == (const BinaryReader& right) const;
                inline bool operator != (const BinaryReader& right) const;

                static inline bool    ToBool(const byte* buffer);
                static inline byte    ToByte(const byte* buffer);
                static inline short   ToShortInt(const byte* buffer);
                static inline int     ToInt(const byte* buffer);
                static inline longint ToLongInt(const byte* buffer);
                static inline float   ToFloat(const byte* buffer);
                static inline double  ToDouble(const byte* buffer);
                static inline Color   ToColor(const byte* buffer);
                static inline Point2  ToPoint2(const byte* buffer);
                static inline Point3  ToPoint3(const byte* buffer);
                static inline Point4  ToPoint4(const byte* buffer);
                static inline Rect    ToRect(const byte* buffer);
                static inline RectF   ToRectF(const byte* buffer);
                static inline Vector2 ToVector2(const byte* buffer);
                static inline Vector3 ToVector3(const byte* buffer);
                static inline Vector4 ToVector4(const byte* buffer);

            private:
                template <typename T> inline T ReadTemplate();
                template <typename T> static inline T ToTemplate(const byte* buffer);

            private:
                StreamPtr sourceStream;
        };
    }

#   include <Bibim/BinaryReader.inl>

#endif