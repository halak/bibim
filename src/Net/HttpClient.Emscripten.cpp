#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_EMSCRIPTEN))

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