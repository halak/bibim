#include <Bibim/PCH.h>
#include <Bibim/HttpClient.Null.h>

namespace Bibim
{
    HttpClient::~HttpClient()
    {
    }

    HttpClient::Response* HttpClient::OnRequest(Request* request)
    {
        return nullptr;
    }
}