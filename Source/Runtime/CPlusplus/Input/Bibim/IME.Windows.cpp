#include <Bibim/Config.h>
#include <Bibim/IME.Windows.h>
#include <vector>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

namespace Bibim
{
    namespace
    {
        static void AlignWord(std::vector<WORD>& v)
        {
            if (v.size() % 2 != 0)
                v.push_back(0);
        }

        static void AppendDWORD(std::vector<WORD>& v, DWORD value)
        {
            v.push_back(LOWORD(value));
            v.push_back(HIWORD(value));
        }

        void AppendString(std::vector<WORD>& v, const wchar_t* s)
        {
            do
            {
                v.push_back(*s);
            } while (*s++);
        }

        static void AppendControl(std::vector<WORD>& v,
                                  DWORD id,
                                  const wchar_t* className,
                                  const wchar_t* caption,
                                  short x,
                                  short y,
                                  short width,
                                  short height,
                                  DWORD style,
                                  DWORD exStyle,
                                  DWORD helpID = 0)
        {
            AlignWord(v);
            AppendDWORD(v, helpID);
            AppendDWORD(v, exStyle);
            AppendDWORD(v, style);
            v.push_back(x);
            v.push_back(y);
            v.push_back(width);
            v.push_back(height);
            AppendDWORD(v, id);
            AppendString(v, className);
            AppendString(v, caption);
            v.push_back(0);
        }

        static void AppendDialog(std::vector<WORD>& v,
                                 const wchar_t* caption,
                                 short x,
                                 short y,
                                 short width,
                                 short height,
                                 DWORD style,
                                 DWORD exStyle,
                                 WORD numberOfChildren,
                                 DWORD helpID = 0)
        {
            style |= WS_CHILD;

            v.push_back(1);
            v.push_back(0xffff);

            AppendDWORD(v, helpID);
            AppendDWORD(v, exStyle);
            AppendDWORD(v, style);

            v.push_back(numberOfChildren);

            v.push_back(x);
            v.push_back(y);
            v.push_back(width);
            v.push_back(height);

            const WORD menuID = 0; // No Menu
            v.push_back(menuID);
            const WORD dialogBoxClass = 0; // Standard Dialog
            v.push_back(dialogBoxClass);

            AppendString(v, caption);

            if (style & DS_SETFONT)
            {
                v.push_back(8);
                v.push_back(FW_NORMAL);
                v.push_back(MAKEWORD(0, DEFAULT_CHARSET));
                AppendString(v, L"MS Sans Serif");
            }
        }

        static void UTF8ToUTF16(std::wstring& utf16, const std::string& utf8)
        {
            utf16.resize(::MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size(), NULL, 0));
            if (utf16.size() > 0)
                ::MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size(), &utf16[0], utf16.size());
        }

        static void UTF16ToUTF8(std::string& utf8, const std::wstring& utf16)
        {
            utf8.resize(::WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), utf16.size(), NULL, 0, NULL, NULL));
            if (utf8.size() > 0)
                ::WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), utf16.size(), &utf8[0], utf8.size(), NULL, NULL);
        }

        static const DWORD IDDESC = 101;
        static const DWORD IDEDIT = 100;
        static INT_PTR CALLBACK DialogProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
        {
            switch (message)
            {
                case WM_SIZE:
                    {
                        static const int PADDING = 5;
                        static const int LINE_HEIGHT = 12;
                        static const int BUTTON_WIDTH = 80;
                        static const int BUTTON_HEIGHT = LINE_HEIGHT * 2;

                        const int WIDTH  = LOWORD(lParam);
                        const int HEIGHT = HIWORD(lParam);

                        ::MoveWindow(::GetDlgItem(windowHandle, IDDESC),
                                     PADDING,
                                     PADDING,
                                     WIDTH - PADDING * 2,
                                     LINE_HEIGHT,
                                     TRUE);
                        ::MoveWindow(::GetDlgItem(windowHandle, IDEDIT),
                                     PADDING,
                                     PADDING + LINE_HEIGHT + PADDING,
                                     WIDTH - PADDING * 2,
                                     HEIGHT - PADDING * 4 - LINE_HEIGHT - BUTTON_HEIGHT,
                                     TRUE);
                        ::MoveWindow(::GetDlgItem(windowHandle, IDOK),
                                     WIDTH - PADDING - BUTTON_WIDTH - PADDING - BUTTON_WIDTH,
                                     HEIGHT - PADDING - BUTTON_HEIGHT,
                                     BUTTON_WIDTH,
                                     BUTTON_HEIGHT,
                                     TRUE);
                        ::MoveWindow(::GetDlgItem(windowHandle, IDCANCEL),
                                     WIDTH - PADDING - BUTTON_WIDTH,
                                     HEIGHT - PADDING - BUTTON_HEIGHT,
                                     BUTTON_WIDTH,
                                     BUTTON_HEIGHT,
                                     TRUE);
                    }
                    break;
                case WM_COMMAND:
                    {
                        const int id = LOWORD(wParam);
                        switch (id)
                        {
                            case IDOK:
                                {
                                    std::wstring editedText;
                                    editedText.resize(512);
                                    const int length = ::GetDlgItemTextW(windowHandle, IDEDIT, &editedText[0], editedText.size());
                                    editedText.resize(length);

                                    std::string* utf8TextPointer = new std::string();
                                    UTF16ToUTF8(*utf8TextPointer, editedText);

                                    EndDialog(windowHandle, reinterpret_cast<INT_PTR>(utf8TextPointer));
                                }
                                break;
                            case IDCANCEL:
                                EndDialog(windowHandle, NULL);
                                break;
                        }
                    }
                    break;
                case WM_INITDIALOG:
                    {
                        RECT clientRect = { 0, 0, 0, 0 };
                        ::GetClientRect(windowHandle, &clientRect);
                        const int w = clientRect.right - clientRect.left;
                        const int h = clientRect.bottom - clientRect.top;
                        ::SendMessage(windowHandle, WM_SIZE, SIZE_RESTORED, MAKELPARAM(w, h));
                    }
                    return TRUE;
            }
        
            return FALSE;
        }
    }

    IME::IME()
    {
    }

    IME::IME(Window* window)
        : Base(window)
    {
    }

    IME::~IME()
    {
    }

    void IME::OnRequest(const Request& request)
    {
        std::wstring wideText;
        std::wstring wideTitle;
        std::wstring wideDescription;
        UTF8ToUTF16(wideText, request.GetText().CStr());
        UTF8ToUTF16(wideTitle, request.GetTitle().CStr());
        UTF8ToUTF16(wideDescription, request.GetDescription().CStr());

        std::vector<WORD> context;
        static const DWORD DialogStyle = WS_CAPTION |
                                         WS_THICKFRAME |
                                         WS_SYSMENU |
                                         WS_POPUP |
                                         WS_VISIBLE |
                                         DS_CENTER |
                                         DS_SETFONT;
        AppendDialog(context,
                     wideTitle.c_str(),
                     100, 100, 300, 100,
                     DialogStyle, 0x00000000,
                     4); // Number of children

        DWORD editStyle = 0;
        switch (request.GetFormat())
        {
            case Number:
                editStyle = ES_NUMBER;
                break;
            case Password:
                editStyle = ES_PASSWORD;
                break;
        }

        AppendControl(context,
                      IDDESC,
                      L"static",
                      wideDescription.c_str(), 
                      0, 0, 0, 0,
                      WS_VISIBLE, 0);
        AppendControl(context,
                      IDEDIT,
                      L"edit",
                      wideText.c_str(),
                      0, 0, 0, 0,
                      WS_VISIBLE | WS_TABSTOP | editStyle, WS_EX_CLIENTEDGE);

        AppendControl(context,
                      IDOK,
                      L"button",
                      L"OK",
                      0, 0, 0, 0,
                      WS_VISIBLE | WS_TABSTOP, 0);
        AppendControl(context,
                      IDCANCEL,
                      L"button",
                      L"Cancel",
                      0, 0, 0, 0,
                      WS_VISIBLE | WS_TABSTOP,
                      0);

        HINSTANCE instanceHandle = GetModuleHandle(NULL);
        DLGTEMPLATE* dialogTemplate = reinterpret_cast<DLGTEMPLATE*>(&context[0]);
        INT_PTR result = ::DialogBoxIndirect(instanceHandle,
                                             dialogTemplate,
                                             0,
                                             DialogProcedure);
        if (result)
        {
            std::string* utf8TextPointer = reinterpret_cast<std::string*>(result);

            request.Submit(utf8TextPointer->c_str());

            delete utf8TextPointer;
        }
        else
        {
            request.Cancel();
        }
    }
}