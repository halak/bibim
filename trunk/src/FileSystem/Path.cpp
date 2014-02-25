#include <Bibim/Config.h>
#include <Bibim/Path.h>

namespace Bibim
{
    String Path::Combine(const String& a, const String& b, const String& c, const String& d, const String& e)
    {
        const String* components[] = { &a, &b, &c, &d, &e };
        
        String result = a;
        for (int i = 1; i < sizeof(components) / sizeof(components[0]); i++)
        {
            const String& s = *components[i];
            if (s.IsEmpty() || (s.GetLength() == 1 && s[0] == '/'))
                continue;

            const bool startsWith = (s[0] == '/');
            const bool endsWith = (result.IsEmpty() == false) ? (result[result.GetLength() - 1] == '/') : false;

            if (startsWith && endsWith)
                result.Append(&s.CStr()[1], s.GetLength() - 1);
            else if ((startsWith && endsWith == false) || (startsWith == false && endsWith))
                result += s;
            else // if (startsWith == false && endsWith == false)
            {
                result += '/';
                result += s;
            }
        }

        return result;
    }

    String Path::GetDirectory(const String& path)
    {
        int directoryIndex = path.ReverseFind('/');
        if (directoryIndex == -1)
            directoryIndex = path.ReverseFind('\\');
        
        if (directoryIndex != -1)
            return path.Substring(0, directoryIndex);
        else
            return String::Empty;
    }

    String Path::GetFileNameWithoutExtension(const String& path)
    {
        int directoryIndex = path.ReverseFind('/');
        if (directoryIndex == -1)
            directoryIndex = path.ReverseFind('\\');

        int extensionIndex = path.ReverseFind('.');
        if (extensionIndex < directoryIndex)
            extensionIndex = -1;

        if (extensionIndex != -1)
        {
            directoryIndex++;
            return path.Substring(directoryIndex, extensionIndex - directoryIndex);
        }
        else
            return path.Substring(directoryIndex + 1);
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