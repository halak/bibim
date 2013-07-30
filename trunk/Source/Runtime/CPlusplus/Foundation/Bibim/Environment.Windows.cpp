#include <Bibim/Config.h>
#include <Bibim/Environment.Windows.h>
#include <windows.h>
#include <Shlobj.h>

namespace Bibim
{
    Environment Environment::PrivateInstance;

    Environment::Environment()
    {
        {
            const LCID locale = ::GetUserDefaultLCID();
            const WORD langID = LOWORD(locale);
            switch (langID)
            {
                case MAKELANGID(LANG_KOREAN, SUBLANG_KOREAN):
                    localeName = "ko-KR";
                    break;
                case MAKELANGID(LANG_JAPANESE, SUBLANG_JAPANESE_JAPAN):
                    localeName = "ja-JP";
                    break;
                default:
                    localeName = "en-US";
                    break;
            }
        }

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
            workingDirectory.Replace('\\', '/');

            BBStackFree(workingDirectoryBuffer);
            BBStackFree(wideWorkingDirectoryBuffer);
        }

        {
            char appDataDirectoryBuffer[MAX_PATH];
            HRESULT result = ::SHGetFolderPathA(nullptr, CSIDL_APPDATA, nullptr, SHGFP_TYPE_CURRENT, appDataDirectoryBuffer);
            if (result == S_OK)
            {
                appDataDirectoryBase = appDataDirectoryBuffer;
                appDataDirectoryBase.Replace('\\', '/');
            }
        }
    }

    String Environment::GetAppDataPath(const String& appName, const String& filename)
    {
        const String directory = PrivateInstance.appDataDirectoryBase + "/" + appName;

        DWORD attributes = ::GetFileAttributesA(directory.CStr());
        if (attributes == INVALID_FILE_ATTRIBUTES)
        {
            if (::CreateDirectoryA(directory.CStr(), nullptr))
                return directory + "/" + filename;
            else
                return PrivateInstance.workingDirectory + "/" + filename;
        }
        else if ((attributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
            return directory + "/" + filename;
        else
            return PrivateInstance.workingDirectory + "/" + filename;
    }
}