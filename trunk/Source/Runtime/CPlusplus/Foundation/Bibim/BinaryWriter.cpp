#include <Bibim/Config.h>
#include <Bibim/BinaryWriter.h>
#include <Bibim/Stream.h>

namespace Bibim
{
    BinaryWriter::BinaryWriter(Stream* sourceStream)
        : sourceStream(sourceStream)
    {
    }

    BinaryWriter::BinaryWriter(const BinaryWriter& original)
        : sourceStream(original.sourceStream)
    {
    }

    BinaryWriter::~BinaryWriter()
    {
    }

    template <typename T> inline void BinaryWriter::WriteToTemplate(Stream* stream, T value)
    {
        BBAssertDebug(stream != nullptr);

        if (stream->Write(&value, sizeof(T)) != sizeof(T))
        {
            // TODO: ERROR
        }
    }

    void BinaryWriter::WriteTo(Stream* stream, bool value)
    {
        WriteToTemplate(stream, value);
    }

    void BinaryWriter::WriteTo(Stream* stream, byte value)
    {
        WriteToTemplate(stream, value);
    }

    void BinaryWriter::WriteTo(Stream* stream, short value)
    {
        WriteToTemplate(stream, value);
    }

    void BinaryWriter::WriteTo(Stream* stream, int value)
    {
        WriteToTemplate(stream, value);
    }

    void BinaryWriter::WriteTo(Stream* stream, longint value)
    {
        WriteToTemplate(stream, value);
    }

    void BinaryWriter::WriteTo(Stream* stream, float value)
    {
        WriteToTemplate(stream, value);
    }

    void BinaryWriter::WriteTo(Stream* stream, double value)
    {
        WriteToTemplate(stream, value);
    }

    void BinaryWriter::WriteTo(Stream* stream, const char* value)
    {
        WriteTo(stream, value, String::CharsLength(value));
    }

    void BinaryWriter::WriteTo(Stream* stream, const char* value, int length)
    {
        BBAssertDebug(stream != nullptr);

        //int writtenSize = 0;

        /*writtenSize = */stream->Write(&length, sizeof(length));
        //BBAssert(writtenSize == sizeof(length));

        /*writtenSize = */stream->Write(value, length);
        //BBAssert(writtenSize == length);
    }

    void BinaryWriter::WriteTo(Stream* stream, const String& value)
    {
        WriteTo(stream, value.CStr(), value.GetLength());
    }

    void BinaryWriter::WriteTo(Stream* stream, Color value)
    {
        WriteToTemplate(stream, value);
    }

    void BinaryWriter::WriteTo(Stream* stream, Point2 value)
    {
        WriteToTemplate(stream, value);
    }

    void BinaryWriter::WriteTo(Stream* stream, Point3 value)
    {
        WriteToTemplate(stream, value);
    }

    void BinaryWriter::WriteTo(Stream* stream, Point4 value)
    {
        WriteToTemplate(stream, value);
    }

    void BinaryWriter::WriteTo(Stream* stream, Rect value)
    {
        WriteToTemplate(stream, value);
    }

    void BinaryWriter::WriteTo(Stream* stream, RectF value)
    {
        WriteToTemplate(stream, value);
    }

    void BinaryWriter::WriteTo(Stream* stream, Vector2 value)
    {
        WriteToTemplate(stream, value);
    }

    void BinaryWriter::WriteTo(Stream* stream, Vector3 value)
    {
        WriteToTemplate(stream, value);
    }

    void BinaryWriter::WriteTo(Stream* stream, Vector4 value)
    {
        WriteToTemplate(stream, value);
    }

    BinaryWriter& BinaryWriter::operator = (const BinaryWriter& right)
    {
        sourceStream = right.sourceStream;
        return *this;
    }
}