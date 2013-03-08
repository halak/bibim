#include <Bibim/Environment.Android.h>

namespace Bibim
{
    Environment Environment::PrivateInstance;

    Environment::Environment()
    {
        PrivateInstance.localeName = "ko-kr";
    }

    String Environment::GetAppDataPath(const String& appName, const String& filename)
    {
        return appName + "\\" + filename;
    }
}