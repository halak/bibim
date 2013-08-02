#pragma once
#ifndef __BIBIM_STREAMWRITER_H__
#define __BIBIM_STREAMWRITER_H__

#include <Bibim/FWD.h>
#include <Bibim/Color.h>
#include <Bibim/Point2.h>
#include <Bibim/Point3.h>
#include <Bibim/Point4.h>
#include <Bibim/Rect.h>
#include <Bibim/RectF.h>
#include <Bibim/Vector2.h>
#include <Bibim/Vector3.h>
#include <Bibim/Vector4.h>

namespace Bibim
{
    class BinaryWriter
    {
        public:
            explicit BinaryWriter(Stream* sourceStream);
            BinaryWriter(const BinaryWriter& original);
            ~BinaryWriter();

            inline void Write(bool value);
            inline void Write(byte value);
            inline void Write(short value);
            inline void Write(int value);
            inline void Write(longint value);
            inline void Write(float value);
            inline void Write(double value);
            inline void Write(const char* value);
            inline void Write(const char* value, int length);
            inline void Write(const String& value);
            inline void Write(Color value);
            inline void Write(Point2 value);
            inline void Write(Point3 value);
            inline void Write(Point4 value);
            inline void Write(Rect value);
            inline void Write(RectF value);
            inline void Write(Vector2 value);
            inline void Write(Vector3 value);
            inline void Write(Vector4 value);

            inline Stream* GetSource() const;

            BinaryWriter& operator = (const BinaryWriter& right);
            inline bool operator == (const BinaryWriter& right) const;
            inline bool operator != (const BinaryWriter& right) const;

            static void WriteTo(Stream* stream, bool value);
            static void WriteTo(Stream* stream, byte value);
            static void WriteTo(Stream* stream, short value);
            static void WriteTo(Stream* stream, int value);
            static void WriteTo(Stream* stream, longint value);
            static void WriteTo(Stream* stream, float value);
            static void WriteTo(Stream* stream, double value);
            static void WriteTo(Stream* stream, const char* value);
            static void WriteTo(Stream* stream, const char* value, int length);
            static void WriteTo(Stream* stream, const String& value);
            static void WriteTo(Stream* stream, Color value);
            static void WriteTo(Stream* stream, Point2 value);
            static void WriteTo(Stream* stream, Point3 value);
            static void WriteTo(Stream* stream, Point4 value);
            static void WriteTo(Stream* stream, Rect value);
            static void WriteTo(Stream* stream, RectF value);
            static void WriteTo(Stream* stream, Vector2 value);
            static void WriteTo(Stream* stream, Vector3 value);
            static void WriteTo(Stream* stream, Vector4 value);

            static inline void From(byte* buffer, bool value);
            static inline void From(byte* buffer, byte value);
            static inline void From(byte* buffer, short value);
            static inline void From(byte* buffer, int value);
            static inline void From(byte* buffer, longint value);
            static inline void From(byte* buffer, float value);
            static inline void From(byte* buffer, double value);
            static inline void From(byte* buffer, Color value);
            static inline void From(byte* buffer, Point2 value);
            static inline void From(byte* buffer, Point3 value);
            static inline void From(byte* buffer, Point4 value);
            static inline void From(byte* buffer, Rect value);
            static inline void From(byte* buffer, RectF value);
            static inline void From(byte* buffer, Vector2 value);
            static inline void From(byte* buffer, Vector3 value);
            static inline void From(byte* buffer, Vector4 value);

        private:
            template <typename T> static inline void WriteToTemplate(Stream* stream, T value);
            template <typename T> static inline void FromTemplate(byte* buffer, T value);

        private:
            StreamPtr sourceStream;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    void BinaryWriter::Write(bool value)
    {
        WriteTo(sourceStream, value);
    }

    void BinaryWriter::Write(byte value)
    {
        WriteTo(sourceStream, value);
    }

    void BinaryWriter::Write(short value)
    {
        WriteTo(sourceStream, value);
    }

    void BinaryWriter::Write(int value)
    {
        WriteTo(sourceStream, value);
    }

    void BinaryWriter::Write(longint value)
    {
        WriteTo(sourceStream, value);
    }

    void BinaryWriter::Write(float value)
    {
        WriteTo(sourceStream, value);
    }

    void BinaryWriter::Write(double value)
    {
        WriteTo(sourceStream, value);
    }

    void BinaryWriter::Write(const char* value)
    {
        WriteTo(sourceStream, value);
    }

    void BinaryWriter::Write(const char* value, int length)
    {
        WriteTo(sourceStream, value, length);
    }

    void BinaryWriter::Write(const String& value)
    {
        WriteTo(sourceStream, value);
    }

    void BinaryWriter::Write(Color value)
    {
        WriteTo(sourceStream, value);
    }

    void BinaryWriter::Write(Point2 value)
    {
        WriteTo(sourceStream, value);
    }

    void BinaryWriter::Write(Point3 value)
    {
        WriteTo(sourceStream, value);
    }

    void BinaryWriter::Write(Point4 value)
    {
        WriteTo(sourceStream, value);
    }

    void BinaryWriter::Write(Rect value)
    {
        WriteTo(sourceStream, value);
    }

    void BinaryWriter::Write(RectF value)
    {
        WriteTo(sourceStream, value);
    }

    void BinaryWriter::Write(Vector2 value)
    {
        WriteTo(sourceStream, value);
    }

    void BinaryWriter::Write(Vector3 value)
    {
        WriteTo(sourceStream, value);
    }

    void BinaryWriter::Write(Vector4 value)
    {
        WriteTo(sourceStream, value);
    }

    Stream* BinaryWriter::GetSource() const
    {
        return sourceStream;
    }

    bool BinaryWriter::operator == (const BinaryWriter& right) const
    {
        return sourceStream == right.sourceStream;
    }

    bool BinaryWriter::operator != (const BinaryWriter& right) const
    {
        return !operator == (right);
    }

    template <typename T> void BinaryWriter::FromTemplate(byte* buffer, T value)
    {
        *(reinterpret_cast<T*>(buffer)) = value;
    }

    void BinaryWriter::From(byte* buffer, bool value)
    {
        (*buffer) = value ? 1 : 0;
    }

    void BinaryWriter::From(byte* buffer, byte value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, short value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, int value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, longint value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, float value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, double value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, Color value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, Point2 value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, Point3 value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, Point4 value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, Rect value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, RectF value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, Vector2 value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, Vector3 value)
    {
        FromTemplate(buffer, value);
    }

    void BinaryWriter::From(byte* buffer, Vector4 value)
    {
        FromTemplate(buffer, value);
    }
}

#endif