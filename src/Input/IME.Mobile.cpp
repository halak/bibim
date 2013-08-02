#include <Bibim/Config.h>
#include <Bibim/IME.Mobile.h>

namespace Bibim
{
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

    bool IME::HasMobileRequest() const
    {
        return requests.empty() == false;
    }

    IME::Request IME::PopMobileRequest()
    {
        Request req = requests.front();
        requests.pop();
        return req;
    }

    void IME::SubmitMobileEdit(int id, const String& text)
    {
        SubmitEdit(id, text);
    }

    void IME::CancelMobileEdit(int id)
    {
        CancelEdit(id);
    }

    void IME::OnRequest(const Request& request)
    {
        requests.push(request);
    }
}