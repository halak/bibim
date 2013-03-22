#include <Bibim/String.h>

namespace Bibim
{
    void Log::Error(const char* message)
    {
        Error(nullptr, message);
    }

    void Log::Warning(const char* message)
    {
        Warning(nullptr, message);
    }

    void Log::Information(const char* message)
    {
        Information(nullptr, message);
    }

    void Log::Error(const char* category, const String& message)
    {
        Error(category, message.CStr());
    }
    
    void Log::Warning(const char* category, const String& message)
    {
        Warning(category, message.CStr());
    }
    
    void Log::Information(const char* category, const String& message)
    {
        Information(category, message.CStr());
    }
}