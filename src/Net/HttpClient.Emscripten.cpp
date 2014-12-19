#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_EMSCRIPTEN) || defined(BIBIM_PLATFORM_IOS))

#include <Bibim/HttpClient.Emscripten.h>

namespace Bibim
{
    HttpClient::HttpClient()
    {
    }

    HttpClient::~HttpClient()
    {
    }

    HttpClient::Response* HttpClient::OnRequest(Request* request)
    {
        return new Response(request, ClientError, String::Empty);
    }
}

#endif