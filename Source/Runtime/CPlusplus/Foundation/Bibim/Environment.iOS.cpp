#include <Bibim/Environment.iOS.h>

namespace Bibim
{
    Environment Environment::PrivateInstance;

    Environment::Environment()
    {
        workingDirectory = String::Empty;
        localeName = String::Empty;
    }

    String Environment::GetAppDataPath(const String& appName, const String& filename)
    {
        return appName + "\\" + filename;
    }
}