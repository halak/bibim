#include <Bibim/Config.h>
#include <Bibim/Clipboard.Android.h>

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