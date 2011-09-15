#include <Bibim/PCH.h>
#include <Bibim/StreamReader.h>
#include <Bibim/Stream.h>

namespace Bibim
{
    StreamReader::StreamReader(Stream* sourceStream)
        : sourceStream(sourceStream)
    {
    }

    StreamReader::StreamReader(const StreamReader& original)
        : sourceStream(original.sourceStream)
    {
    }

    StreamReader::~StreamReader()
    {
    }

    template <typename T> T StreamReader::ReadTemplate()
    {
        BBAssertDebug(sourceStream != nullptr);

        T result = 0;
        if (sourceStream->Read(&result, sizeof(T)) == sizeof(T))
            return result;
        else
        {
            // TODO: ERROR
            return T();
        }
    }

    bool StreamReader::ReadBool()
    {
        return ReadTemplate<bool>();
    }

    int StreamReader::ReadInt()
    {
        return ReadTemplate<int>();
    }

    float StreamReader::ReadFloat()
    {
        return ReadTemplate<float>();
    }

    String StreamReader::ReadString()
    {
        BBAssertDebug(sourceStream != nullptr);

        int readSize = 0;
        int length = 0;
        
        readSize = sourceStream->Read(&length, sizeof(length));
        BBAssert(readSize == sizeof(length));

        char* buffer = BBStackAlloc(char, length);
        readSize = sourceStream->Read(buffer, length);
        BBAssert(readSize == length);
        
        const String result = String(buffer, 0, length);
        
        BBStackFree(buffer);

        return result;
    }

    StreamReader& StreamReader::operator = (const StreamReader& right)
    {
        sourceStream = right.sourceStream;
        return *this;
    }
}