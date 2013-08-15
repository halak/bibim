#pragma once
#ifndef __BIBIM_BINARYREADER_H__
#define __BIBIM_BINARYREADER_H__

#include <Bibim/FWD.h>
#include <Bibim/Color.h>
#include <Bibim/Point2.h>
#include <Bibim/Point3.h>
#include <Bibim/Point4.h>
#include <Bibim/Rect.h>
#include <Bibim/RectF.h>
#include <Bibim/String.h>
#include <Bibim/Vector2.h>
#include <Bibim/Vector3.h>
#include <Bibim/Vector4.h>

namespace Bibim
{
    class BinaryReader
    {
        public:
            explicit BinaryReader(Stream* sourceStream);
            BinaryReader(const BinaryReader& original);
            ~BinaryReader();

            inline void*   Read(void* buffer, int length);
            inline bool    ReadBool();
            inline byte    ReadByte();
            inline short   ReadShortInt();
            inline int     ReadInt();
            inline longint ReadLongInt();
            inline float   ReadFloat();
            inline double  ReadDouble();
            inline String  ReadString();
            inline Color   ReadColor();
            inline Point2  ReadPoint2();
            inline Point3  ReadPoint3();
            inline Point4  ReadPoint4();
            inline Rect    ReadRect();
            inline RectF   ReadRectF();
            inline Vector2 ReadVector2();
            inline Vector3 ReadVector3();
            inline Vector4 ReadVector4();

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

            static void*   ReadFrom(Stream* stream, void* buffer, int length);
            static bool    ReadBoolFrom(Stream* stream);
            static byte    ReadByteFrom(Stream* stream);
            static short   ReadShortIntFrom(Stream* stream);
            static int     ReadIntFrom(Stream* stream);
            static longint ReadLongIntFrom(Stream* stream);
            static float   ReadFloatFrom(Stream* stream);
            static double  ReadDoubleFrom(Stream* stream);
            static String  ReadStringFrom(Stream* stream);
            static Color   ReadColorFrom(Stream* stream);
            static Point2  ReadPoint2From(Stream* stream);
            static Point3  ReadPoint3From(Stream* stream);
            static Point4  ReadPoint4From(Stream* stream);
            static Rect    ReadRectFrom(Stream* stream);
            static RectF   ReadRectFFrom(Stream* stream);
            static Vector2 ReadVector2From(Stream* stream);
            static Vector3 ReadVector3From(Stream* stream);
            static Vector4 ReadVector4From(Stream* stream);

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
            template <typename T> static inline T ReadFromTemplate(Stream* stream);
            template <typename T> static inline T ToTemplate(const byte* buffer);

        private:
            StreamPtr sourceStream;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    void* BinaryReader::Read(void* buffer, int length)
    {
        return ReadFrom(sourceStream, buffer, length);
    }

    bool BinaryReader::ReadBool()
    {
        return ReadBoolFrom(sourceStream);
    }

    byte BinaryReader::ReadByte()
    {
        return ReadByteFrom(sourceStream);
    }

    short BinaryReader::ReadShortInt()
    {
        return ReadShortIntFrom(sourceStream);
    }

    int BinaryReader::ReadInt()
    {
        return ReadIntFrom(sourceStream);
    }

    longint BinaryReader::ReadLongInt()
    {
        return ReadLongIntFrom(sourceStream);
    }

    float BinaryReader::ReadFloat()
    {
        return ReadFloatFrom(sourceStream);
    }

    double BinaryReader::ReadDouble()
    {
        return ReadDoubleFrom(sourceStream);
    }

    String BinaryReader::ReadString()
    {
        return ReadStringFrom(sourceStream);
    }

    Color BinaryReader::ReadColor()
    {
        return ReadColorFrom(sourceStream);
    }

    Point2 BinaryReader::ReadPoint2()
    {
        return ReadPoint2From(sourceStream);
    }

    Point3 BinaryReader::ReadPoint3()
    {
        return ReadPoint3From(sourceStream);
    }

    Point4 BinaryReader::ReadPoint4()
    {
        return ReadPoint4From(sourceStream);
    }

    Rect BinaryReader::ReadRect()
    {
        return ReadRectFrom(sourceStream);
    }

    RectF BinaryReader::ReadRectF()
    {
        return ReadRectFFrom(sourceStream);
    }

    Vector2 BinaryReader::ReadVector2()
    {
        return ReadVector2From(sourceStream);
    }

    Vector3 BinaryReader::ReadVector3()
    {
        return ReadVector3From(sourceStream);
    }

    Vector4 BinaryReader::ReadVector4()
    {
        return ReadVector4From(sourceStream);
    }

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