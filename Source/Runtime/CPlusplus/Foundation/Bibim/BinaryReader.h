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

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void BinaryReader::Read(bool& outValue)
        {
            outValue = ReadBool();
        }

        void BinaryReader::Read(byte& outValue)
        {
            outValue = ReadByte();
        }

        void BinaryReader::Read(short& outValue)
        {
            outValue = ReadShortInt();
        }

        void BinaryReader::Read(int& outValue)
        {
            outValue = ReadInt();
        }

        void BinaryReader::Read(longint& outValue)
        {
            outValue = ReadLongInt();
        }

        void BinaryReader::Read(float& outValue)
        {
            outValue = ReadFloat();
        }

        void BinaryReader::Read(double& outValue)
        {
            outValue = ReadDouble();
        }

        void BinaryReader::Read(String& outValue)
        {
            outValue = ReadString();
        }

        void BinaryReader::Read(Color& outValue)
        {
            outValue = ReadColor();
        }

        void BinaryReader::Read(Point2& outValue)
        {
            outValue = ReadPoint2();
        }

        void BinaryReader::Read(Point3& outValue)
        {
            outValue = ReadPoint3();
        }

        void BinaryReader::Read(Point4& outValue)
        {
            outValue = ReadPoint4();
        }

        void BinaryReader::Read(Rect& outValue)
        {
            outValue = ReadRect();
        }

        void BinaryReader::Read(RectF& outValue)
        {
            outValue = ReadRectF();
        }

        void BinaryReader::Read(Vector2& outValue)
        {
            outValue = ReadVector2();
        }

        void BinaryReader::Read(Vector3& outValue)
        {
            outValue = ReadVector3();
        }

        void BinaryReader::Read(Vector4& outValue)
        {
            outValue = ReadVector4();
        }

        Stream* BinaryReader::GetSource() const
        {
            return sourceStream;
        }

        bool BinaryReader::operator == (const BinaryReader& right) const
        {
            return sourceStream == right.sourceStream;
        }

        bool BinaryReader::operator != (const BinaryReader& right) const
        {
            return !operator == (right);
        }

        template <typename T> T BinaryReader::ToTemplate(const byte* buffer)
        {
            return *reinterpret_cast<const T*>(buffer);
        }

        bool BinaryReader::ToBool(const byte* buffer)
        {
            return (*buffer) != 0;
        }

        byte BinaryReader::ToByte(const byte* buffer)
        {
            return ToTemplate<byte>(buffer);
        }

        short BinaryReader::ToShortInt(const byte* buffer)
        {
            return ToTemplate<short>(buffer);
        }

        int BinaryReader::ToInt(const byte* buffer)
        {
            return ToTemplate<int>(buffer);
        }

        longint BinaryReader::ToLongInt(const byte* buffer)
        {
            return ToTemplate<longint>(buffer);
        }

        float BinaryReader::ToFloat(const byte* buffer)
        {
            return ToTemplate<float>(buffer);
        }

        double BinaryReader::ToDouble(const byte* buffer)
        {
            return ToTemplate<double>(buffer);
        }

        Color BinaryReader::ToColor(const byte* buffer)
        {
            return ToTemplate<Color>(buffer);
        }

        Point2 BinaryReader::ToPoint2(const byte* buffer)
        {
            return ToTemplate<Point2>(buffer);
        }

        Point3 BinaryReader::ToPoint3(const byte* buffer)
        {
            return ToTemplate<Point3>(buffer);
        }

        Point4 BinaryReader::ToPoint4(const byte* buffer)
        {
            return ToTemplate<Point4>(buffer);
        }

        Rect BinaryReader::ToRect(const byte* buffer)
        {
            return ToTemplate<Rect>(buffer);
        }

        RectF BinaryReader::ToRectF(const byte* buffer)
        {
            return ToTemplate<RectF>(buffer);
        }

        Vector2 BinaryReader::ToVector2(const byte* buffer)
        {
            return ToTemplate<Vector2>(buffer);
        }

        Vector3 BinaryReader::ToVector3(const byte* buffer)
        {
            return ToTemplate<Vector3>(buffer);
        }

        Vector4 BinaryReader::ToVector4(const byte* buffer)
        {
            return ToTemplate<Vector4>(buffer);
        }
    }

#endif