#include <Bibim/Config.h>
#include <Bibim/Environment.Android.h>

namespace Bibim
{
    Environment Environment::PrivateInstance;

    Environment::Environment()
    {
    }

    void Environment::Setup(const String& localeName, const String& workingDirectory)
    {
        PrivateInstance.localeName = localeName;
        PrivateInstance.workingDirectory = workingDirectory;
    }

    String Environment::GetAppDataPath(const String& /*appName*/, const String& filename)
    {
        return PrivateInstance.workingDirectory + filename;
    }
}