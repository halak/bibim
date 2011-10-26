#include <Bibim/PCH.h>
#include <Bibim/SystemLogger.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))
#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>
#endif

namespace Bibim
{
    SystemLogger::SystemLogger()
    {
    }

    SystemLogger::~SystemLogger()
    {
    }

    void SystemLogger::Write(const char* head, const char* category, const char* message)
    {
#       if (defined(BIBIM_PLATFORM_WINDOWS))
        ::OutputDebugString(head);
        ::OutputDebugString(category);
        ::OutputDebugString(message);
        ::OutputDebugString("\n");
#       endif
    }

    void SystemLogger::Error(const char* category, const char* message)
    {
        Write("<ERROR>       ", category, message);
    }

    void SystemLogger::Warning(const char* category, const char* message)
    {
        Write("<WARNING>     ", category, message);
    }

    void SystemLogger::Information(const char* category, const char* message)
    {
        Write("<INFORMATION> ", category, message);
    }
}