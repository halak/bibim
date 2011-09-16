#include <Bibim/PCH.h>
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
        WriteTemplate<bool>(value);
    }

    void BinaryWriter::Write(int8 value)
    {
        WriteTemplate<int8>(value);
    }

    void BinaryWriter::Write(uint8 value)
    {
        WriteTemplate<uint8>(value);
    }

    void BinaryWriter::Write(int16 value)
    {
        WriteTemplate<int16>(value);
    }

    void BinaryWriter::Write(uint16 value)
    {
        WriteTemplate<uint16>(value);
    }

    void BinaryWriter::Write(int32 value)
    {
        WriteTemplate<int32>(value);
    }

    void BinaryWriter::Write(uint32 value)
    {
        WriteTemplate<uint32>(value);
    }

    void BinaryWriter::Write(int64 value)
    {
        WriteTemplate<int64>(value);
    }

    void BinaryWriter::Write(uint64 value)
    {
        WriteTemplate<uint64>(value);
    }

    void BinaryWriter::Write(float value)
    {
        WriteTemplate<float>(value);
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

    BinaryWriter& BinaryWriter::operator = (const BinaryWriter& right)
    {
        sourceStream = right.sourceStream;
        return *this;
    }
}