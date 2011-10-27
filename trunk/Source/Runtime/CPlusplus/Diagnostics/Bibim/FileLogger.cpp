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
            if (category)
            {
                const int categoryLength = String::CharsLength(category);
                const int messageLength  = String::CharsLength(message);
                const int fullLength = headLength + 1 + categoryLength + 2 + messageLength + 2;
                char* full = BBStackAlloc(char, fullLength);
                char* s = full;
                s += String::CopyChars(s, head, headLength);
                (*s++) = '[';
                s += String::CopyChars(s, category, categoryLength);
                (*s++) = ']';
                (*s++) = ' ';
                s += String::CopyChars(s, message, messageLength);
                (*s++) = '\r';
                (*s++) = '\n';
                stream->Write(full, fullLength);
                stream->Flush();
                BBStackFree(full);
            }
            else
            {
                const int messageLength  = String::CharsLength(message);
                const int fullLength = headLength + messageLength + 2;
                char* full = BBStackAlloc(char, fullLength);
                char* s = full;
                s += String::CopyChars(s, head, headLength);
                s += String::CopyChars(s, message, messageLength);
                (*s++) = '\r';
                (*s++) = '\n';
                stream->Write(full, fullLength);
                stream->Flush();
                BBStackFree(full);
            }
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