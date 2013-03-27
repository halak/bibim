#include <Bibim/PCH.h>
#include <Bibim/IMEBase.h>

namespace Bibim
{
    IMEBase::IMEBase()
        : window(nullptr),
          lastCallbackID(0)
    {
    }

    IMEBase::IMEBase(Window* window)
        : window(window),
          lastCallbackID(0)
    {
    }

    IMEBase::~IMEBase()
    {
    }

    void IMEBase::Edit(const String& text,
                       const String& title,
                       const String& description,
                       TextFormat format,
                       int maxLength,
                       Callback* callback)
    {
        const int callbackID = RegisterCallback(callback);
        if (callbackID != -1)
            OnRequest(Request(this, callbackID, text, title, description, format, maxLength));
    }

    void IMEBase::SubmitEdit(int callbackID, const String& text)
    {
        if (Callback* callback = UnregisterCallback(callbackID))
            callback->OnTextEdited(text);
    }

    void IMEBase::CancelEdit(int callbackID)
    {
        if (Callback* callback = UnregisterCallback(callbackID))
            callback->OnTextEditCancelled();
    }

    int IMEBase::RegisterCallback(Callback* callback)
    {
        if (callback == nullptr)
            return -1;

        int id = lastCallbackID++;
        callbacks[id] = callback;
        return id;
    }

    IMEBase::Callback* IMEBase::UnregisterCallback(int callbackID)
    {
        CallbackMap::iterator it = callbacks.find(callbackID);
        if (it != callbacks.end())
        {
            Callback* callback = (*it).second;
            callbacks.erase(it);

            return callback;
        }
        else
            return nullptr;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    IMEBase::Request::Request()
        : ime(nullptr),
          id(-1),
          format(Plain),
          maxLength(0)
    {
    }

    IMEBase::Request::Request(IMEBase* ime, int id, const String& text, const String& title, const String& description, TextFormat format, int maxLength)
        : ime(ime),
          id(id),
          text(text),
          title(title),
          description(description),
          format(format),
          maxLength(maxLength)
    {
    }

    IMEBase::Request::Request(const Request& original)
        : ime(original.ime),
          id(original.id),
          text(original.text),
          title(original.title),
          description(original.description),
          format(original.format),
          maxLength(original.maxLength)
    {
    }

    IMEBase::Request::~Request()
    {
    }

    void IMEBase::Request::Submit(const String& value) const
    {
        if (ime)
            ime->SubmitEdit(id, value);
    }

    void IMEBase::Request::Cancel() const
    {
        if (ime)
            ime->CancelEdit(id);
    }

    IMEBase::Request& IMEBase::Request::operator = (const Request& right)
    {
        ime = right.ime;
        id = right.id;
        text = right.text;
        title = right.title;
        description = right.description;
        format = right.format;
        maxLength = right.maxLength;
        return *this;
    }
}