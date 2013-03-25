#include <Bibim/PCH.h>
#include <Bibim/Path.h>

namespace Bibim
{
    String Path::GetDirectory(const String& path)
    {
        int directoryIndex = path.ReverseFind('\\');
        if (directoryIndex == -1)
            directoryIndex = path.ReverseFind('/');
        
        return path.Substring(0, directoryIndex);
    }

    bool Path::IsAbsolutePath(const String& path)
    {
        if (path.GetLength() >= 2)
        {
            const char* s = path.CStr();
            return (s[0] == '/' ||
                    s[1] == ':' ||
                    s[2] == ':');
        }
        else
            return false;
    }
}