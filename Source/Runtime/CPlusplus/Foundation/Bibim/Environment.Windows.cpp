#include <Bibim/Environment.Windows.h>
#include <windows.h>

namespace Bibim
{
    Environment Environment::PrivateInstance;

    Environment::Environment()
    {
        const DWORD workingDirectoryLength = ::GetCurrentDirectory(0, nullptr);
        char* workingDirectoryBuffer = BBStackAlloc(char, workingDirectoryLength);

        ::GetCurrentDirectory(workingDirectoryLength, workingDirectoryBuffer);
        workingDirectoryBuffer[workingDirectoryLength - 1] = '\0';

        workingDirectory = workingDirectoryBuffer;

        BBStackFree(workingDirectoryBuffer);
    }
}