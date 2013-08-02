#include <Bibim/Config.h>
#include <Bibim/Log.h>
#include <Bibim/BinaryWriter.h>
#include <Bibim/Diagnostics.h>
#include <Bibim/Stream.h>

namespace Bibim
{
    void Log::Write(Level level, const char* category, const char* message)
    {
        Stream* stream = Diagnostics::GetStream();
        if (stream == nullptr)
            return;

        if (category == nullptr)
            category = "";
        if (message == nullptr)
            message = "";

        BinaryWriter::WriteTo(stream, static_cast<int>(Diagnostics::LogProtocolID));
        BinaryWriter::WriteTo(stream, static_cast<byte>(level));
        BinaryWriter::WriteTo(stream, category);
        BinaryWriter::WriteTo(stream, message);
    }
}