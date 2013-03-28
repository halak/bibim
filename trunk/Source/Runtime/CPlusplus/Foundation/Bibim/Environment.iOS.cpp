#include <Bibim/PCH.h>
#include <Bibim/Environment.iOS.h>

namespace Bibim
{
    Environment Environment::PrivateInstance;

    Environment::Environment()
    {
    }

    void Environment::Setup(const String& localeName,
                            const String& workingDirectory,
                            const String& appDataDirectoryBase)
    {
        PrivateInstance.localeName = localeName;
        PrivateInstance.workingDirectory = workingDirectory;
        PrivateInstance.appDataDirectoryBase = appDataDirectoryBase;
    }

    String Environment::GetAppDataPath(const String& appName, const String& filename)
    {
        return PrivateInstance.appDataDirectoryBase + "/" + filename;
    }
}