#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_EMSCRIPTEN))

#include <Bibim/Clipboard.Emscripten.h>

namespace Bibim
{
    Clipboard::Clipboard()
    {
    }

    Clipboard::~Clipboard()
    {
    }
                
    String Clipboard::GetText() const
    {
        return String::Empty;
    }

    void Clipboard::SetText(const String& value)
    {
    }
}

#endif