#include <Bibim/PCH.h>
#include <Bibim/IME.h>

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

    bool IME::HasAndroidRequest() const
    {
        return requests.empty() == false;
    }

    IME::Request IME::PopAndroidRequest()
    {
        Request req = requests.front();
        requests.pop();
        return req;
    }

    void IME::SubmitAndroidEdit(int id, const String& text)
    {
        SubmitEdit(id, text);
    }

    void IME::CancelAndroidEdit(int id)
    {
        CancelEdit(id);
    }

    void IME::OnRequest(const Request& request)
    {
        requests.push(request);
    }
}