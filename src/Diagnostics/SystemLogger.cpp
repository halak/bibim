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
#       if (defined(BIBIM_PLATFORM_ANDROID))
            struct HeadToLogPriority
            {
                static android_LogPriority Do(const char* head)
                {
                    switch (head[1])
                    {
                        case 'E': return ANDROID_LOG_ERROR;
                        case 'W': return ANDROID_LOG_WARN;
                        case 'I': return ANDROID_LOG_INFO;
                        default:  return ANDROID_LOG_VERBOSE;
                    }
                }
            };
#       endif

        if (category)
        {
#           if (defined(BIBIM_PLATFORM_WINDOWS))
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
                ::OutputDebugString(full);
                BBStackFree(full);
#           elif (defined(BIBIM_PLATFORM_ANDROID))
                __android_log_print(HeadToLogPriority::Do(head), category, message);
#           endif
        }
        else
        {
#           if (defined(BIBIM_PLATFORM_WINDOWS))
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
                ::OutputDebugString(full);
                BBStackFree(full);
#           elif (defined(BIBIM_PLATFORM_ANDROID))
                __android_log_print(HeadToLogPriority::Do(head), GetName().CStr(), message);
#           endif
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