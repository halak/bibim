#include <Bibim/Config.h>
#include <Bibim/Log.h>
#include <Bibim/BinaryWriter.h>
#include <Bibim/Stream.h>

namespace Bibim
{
    StreamPtr Log::stream;

    void Log::Write(Level level, const char* category, const char* message)
    {
        static const int LOG_ID = 1000;

        if (stream == nullptr)
            return;
        if (category == nullptr)
            category = "";
        if (message == nullptr)
            message = "";

        // PROTOCOL
        BinaryWriter::WriteTo(stream, LOG_ID);
        BinaryWriter::WriteTo(stream, static_cast<byte>(level));
        BinaryWriter::WriteTo(stream, category);
        BinaryWriter::WriteTo(stream, message);
    }

    void Log::SetStream(Stream* value)
    {
        stream = value;
    }
}