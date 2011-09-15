#include <Bibim/PCH.h>
#include <Bibim/StreamWriter.h>
#include <Bibim/Stream.h>

namespace Bibim
{
    StreamWriter::StreamWriter(Stream* sourceStream)
        : sourceStream(sourceStream)
    {
    }

    StreamWriter::StreamWriter(const StreamWriter& original)
        : sourceStream(original.sourceStream)
    {
    }

    StreamWriter::~StreamWriter()
    {
    }

    template <typename T> inline void StreamWriter::WriteTemplate(T value)
    {
        BBAssertDebug(sourceStream != nullptr);

        if (sourceStream->Write(&value, sizeof(T)) != sizeof(T))
        {
            // TODO: ERROR
        }
    }

    void StreamWriter::Write(bool value)
    {
        WriteTemplate<bool>(value);
    }

    void StreamWriter::Write(int32 value)
    {
        WriteTemplate<int32>(value);
    }

    void StreamWriter::Write(uint32 value)
    {
        WriteTemplate<uint32>(value);
    }

    void StreamWriter::Write(float value)
    {
        WriteTemplate<float>(value);
    }

    void StreamWriter::Write(const char* value)
    {
        Write(value, strlen(value));
    }

    void StreamWriter::Write(const char* value, int length)
    {
        BBAssertDebug(sourceStream != nullptr);

        int writtenSize = 0;

        writtenSize = sourceStream->Write(&length, sizeof(length));
        BBAssert(writtenSize == sizeof(length));

        writtenSize = sourceStream->Write(value, length);
        BBAssert(writtenSize == length);
    }

    void StreamWriter::Write(const String& value)
    {
        Write(value.CStr(), value.GetLength());
    }

    StreamWriter& StreamWriter::operator = (const StreamWriter& right)
    {
        sourceStream = right.sourceStream;
        return *this;
    }
}