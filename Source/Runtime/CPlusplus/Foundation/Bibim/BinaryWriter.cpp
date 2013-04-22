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

    template <typename T> inline void BinaryWriter::WriteTemplate(T value)
    {
        BBAssertDebug(sourceStream != nullptr);

        if (sourceStream->Write(&value, sizeof(T)) != sizeof(T))
        {
            // TODO: ERROR
        }
    }

    void BinaryWriter::Write(bool value)
    {
        WriteTemplate(value);
    }

    void BinaryWriter::Write(byte value)
    {
        WriteTemplate(value);
    }

    void BinaryWriter::Write(short value)
    {
        WriteTemplate(value);
    }

    void BinaryWriter::Write(int value)
    {
        WriteTemplate(value);
    }

    void BinaryWriter::Write(longint value)
    {
        WriteTemplate(value);
    }

    void BinaryWriter::Write(float value)
    {
        WriteTemplate(value);
    }

    void BinaryWriter::Write(double value)
    {
        WriteTemplate(value);
    }

    void BinaryWriter::Write(const char* value)
    {
        Write(value, strlen(value));
    }

    void BinaryWriter::Write(const char* value, int length)
    {
        BBAssertDebug(sourceStream != nullptr);

        int writtenSize = 0;

        writtenSize = sourceStream->Write(&length, sizeof(length));
        BBAssert(writtenSize == sizeof(length));

        writtenSize = sourceStream->Write(value, length);
        BBAssert(writtenSize == length);
    }

    void BinaryWriter::Write(const String& value)
    {
        Write(value.CStr(), value.GetLength());
    }

    void BinaryWriter::Write(Color value)
    {
        WriteTemplate(value);
    }

    void BinaryWriter::Write(Point2 value)
    {
        WriteTemplate(value);
    }

    void BinaryWriter::Write(Point3 value)
    {
        WriteTemplate(value);
    }

    void BinaryWriter::Write(Point4 value)
    {
        WriteTemplate(value);
    }

    void BinaryWriter::Write(Rect value)
    {
        WriteTemplate(value);
    }

    void BinaryWriter::Write(RectF value)
    {
        WriteTemplate(value);
    }

    void BinaryWriter::Write(Vector2 value)
    {
        WriteTemplate(value);
    }

    void BinaryWriter::Write(Vector3 value)
    {
        WriteTemplate(value);
    }

    void BinaryWriter::Write(Vector4 value)
    {
        WriteTemplate(value);
    }

    BinaryWriter& BinaryWriter::operator = (const BinaryWriter& right)
    {
        sourceStream = right.sourceStream;
        return *this;
    }
}