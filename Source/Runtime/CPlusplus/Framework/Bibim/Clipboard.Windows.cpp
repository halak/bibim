#include <Bibim/Config.h>
#include <Bibim/Clipboard.Windows.h>
#include <windows.h>

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
        if (::OpenClipboard(nullptr))
        {
            String value = String::Empty;

            if (::IsClipboardFormatAvailable(CF_TEXT) ||
                ::IsClipboardFormatAvailable(CF_OEMTEXT))
            {
                HANDLE dataHandle = ::GetClipboardData(CF_TEXT);
                value = static_cast<const char*>(::GlobalLock(dataHandle));
                ::GlobalUnlock(dataHandle);
            }

            ::CloseClipboard();

            return value;
        }
        else
            return String::Empty;
    }

    void Clipboard::SetText(const String& value)
    {
        if (::OpenClipboard(nullptr))
        {
            ::EmptyClipboard();

            HGLOBAL dataHandle = ::GlobalAlloc(GMEM_DDESHARE,
                                               value.GetLength() + 1);

            char* destination = static_cast<char*>(::GlobalLock(dataHandle));

            String::CopyChars(destination, value.CStr(), value.GetLength());
            destination[value.GetLength()] = '\0';

            ::GlobalUnlock(dataHandle);

            ::SetClipboardData(CF_TEXT, dataHandle);

            ::CloseClipboard();
        }
    }
}