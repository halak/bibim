#include <Bibim/Config.h>
#include <Bibim/SystemLogger.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))
#   ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#   endif
#   include <windows.h>
#elif (defined(BIBIM_PLATFORM_ANDROID))
#   include <android/log.h>
#endif

namespace Bibim
{
    SystemLogger::SystemLogger()
    {
    }

    SystemLogger::SystemLogger(const String& name)
        : name(name)
    {
    }

    SystemLogger::~SystemLogger()
    {
    }

    void SystemLogger::Write(const char* head, const char* category, const char* message)
    {
        if (category)
        {
            const int headLength = String::CharsLength(head);
            const int categoryLength = String::CharsLength(category);
            const int messageLength = String::CharsLength(message);
            char* full = BBStackAlloc(char, 1 + name.GetLength() + 2 + headLength + 1 + categoryLength + 2 + messageLength + 1 + 1);
            char* s = full;
            (*s++) = '(';
            s += String::CopyChars(s, name.CStr(), name.GetLength());
            (*s++) = ')';
            (*s++) = ' ';
            s += String::CopyChars(s, head, headLength);
            (*s++) = '[';
            s += String::CopyChars(s, category, categoryLength);
            (*s++) = ']';
            (*s++) = ' ';
            s += String::CopyChars(s, message, messageLength);
            (*s++) = '\n';
            (*s++) = '\0';
#           if (defined(BIBIM_PLATFORM_WINDOWS))
                ::OutputDebugString(full);
#           elif (defined(BIBIM_PLATFORM_ANDROID))
                __android_log_print(ANDROID_LOG_INFO, GetName().CStr(), full);
#           endif
            BBStackFree(full);
        }
        else
        {
            const int headLength = String::CharsLength(head);
            const int messageLength = String::CharsLength(message);
            char* full = BBStackAlloc(char, 1 + name.GetLength() + 2 + headLength + messageLength + 1 + 1);
            char* s = full;
            (*s++) = '(';
            s += String::CopyChars(s, name.CStr(), name.GetLength());
            (*s++) = ')';
            (*s++) = ' ';
            s += String::CopyChars(s, head, headLength);
            s += String::CopyChars(s, message, messageLength);
            (*s++) = '\n';
            (*s++) = '\0';
#           if (defined(BIBIM_PLATFORM_WINDOWS))
                ::OutputDebugString(full);
#           elif (defined(BIBIM_PLATFORM_ANDROID))
                __android_log_print(ANDROID_LOG_INFO, GetName().CStr(), full);
#           endif
            BBStackFree(full);
        }
    }

    void SystemLogger::Error(const char* category, const char* message)
    {
        Write("<ERROR> ", category, message);
    }

    void SystemLogger::Warning(const char* category, const char* message)
    {
        Write("<WARN>  ", category, message);
    }

    void SystemLogger::Information(const char* category, const char* message)
    {
        Write("<INFO>  ", category, message);
    }
}