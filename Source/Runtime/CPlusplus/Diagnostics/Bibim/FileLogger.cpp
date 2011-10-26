#include <Bibim/PCH.h>
#include <Bibim/FileLogger.h>
#include <Bibim/FileStream.h>

namespace Bibim
{
    FileLogger::FileLogger()
    {
    }

    FileLogger::FileLogger(const String& path)
    {
        stream = new FileStream(path, FileStream::WriteOnly);
        stream->Write(String::UTF8BOM, sizeof(String::UTF8BOM));
    }

    FileLogger::~FileLogger()
    {
    }

    void FileLogger::Write(const char* head, int headLength, const char* category, const char* message)
    {
        if (stream)
        {
            stream->Write(head, headLength);

            if (category)
            {
                stream->Write("[",  1);
                stream->Write(category, String::CharsLength(category));
                stream->Write("] ", 2);
            }

            stream->Write(message, String::CharsLength(message));
            stream->Write("\r\n", 2);
            stream->Flush();
        }
    }

    void FileLogger::Error(const char* category, const char* message)
    {
        Write("<ERROR>       ", 14, category, message);
    }

    void FileLogger::Warning(const char* category, const char* message)
    {
        Write("<WARNING>     ", 14, category, message);
    }

    void FileLogger::Information(const char* category, const char* message)
    {
        Write("<INFORMATION> ", 14, category, message);
    }

    void FileLogger::SetPath(const String& value)
    {
        if (path.EqualsIgnoreCase(value) == false)
        {
            path = value;
            stream = new FileStream(path, FileStream::WriteOnly);
            stream->Write(String::UTF8BOM, sizeof(String::UTF8BOM));
        }
    }
}