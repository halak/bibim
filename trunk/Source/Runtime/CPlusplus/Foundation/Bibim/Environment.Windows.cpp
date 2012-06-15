#include <Bibim/Environment.Windows.h>
#include <windows.h>

namespace Bibim
{
    Environment Environment::PrivateInstance;

    Environment::Environment()
    {
        const DWORD wideWorkingDirectoryLength = ::GetCurrentDirectoryW(0, nullptr);
        wchar_t* wideWorkingDirectoryBuffer = BBStackAlloc(wchar_t, wideWorkingDirectoryLength);

        ::GetCurrentDirectoryW(wideWorkingDirectoryLength, wideWorkingDirectoryBuffer);
        wideWorkingDirectoryBuffer[wideWorkingDirectoryLength - 1] = '\0';

        const int workingDirectoryLength = ::WideCharToMultiByte(CP_UTF8, 0, wideWorkingDirectoryBuffer, wideWorkingDirectoryLength, nullptr, 0, nullptr, nullptr);
        char* workingDirectoryBuffer = BBStackAlloc(char, workingDirectoryLength);

        ::WideCharToMultiByte(CP_UTF8, 0, wideWorkingDirectoryBuffer, wideWorkingDirectoryLength, workingDirectoryBuffer, workingDirectoryLength, nullptr, nullptr);
        workingDirectoryBuffer[workingDirectoryLength - 1] = '\0';

        workingDirectory = workingDirectoryBuffer;

        BBStackFree(workingDirectoryBuffer);
        BBStackFree(wideWorkingDirectoryBuffer);
    }
}