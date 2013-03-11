#include <Bibim/PCH.h>
#include <Bibim/HttpClient.Curl.h>
#include <curl/curl.h>

namespace Bibim
{
    struct NetworkStream
    {
        int id;
    };

    struct Header : public NetworkStream
    {
        static const int ID = 0;
        String contentType;
    };

    struct Body : NetworkStream
    {
        static const int ID = 1;
        std::vector<char> content;
    };

    static size_t OnRecv(void* ptr, size_t size, size_t nmemb, void* stream)
    {
        const char* source = reinterpret_cast<const char*>(ptr);
        switch (reinterpret_cast<NetworkStream*>(stream)->id)
        {
            case Header::ID:
                {
                    static const String contentTypeKey = "Content-Type:";

                    Header* header = reinterpret_cast<Header*>(stream);
                    String headerItem = String(source, 0, size * nmemb);
                    if (headerItem.StartsWith(contentTypeKey))
                        header->contentType = headerItem.Substring(contentTypeKey.GetLength());
                }
                return nmemb;
            case Body::ID:
                {
                    Body* body = reinterpret_cast<Body*>(stream);
                    body->content.reserve(body->content.capacity() + size * nmemb);
                    body->content.insert(body->content.end(), &source[0], &source[size * nmemb]);
                }
                return nmemb;
            default:
                return 0;
        }
    }

    HttpClient::HttpClient()
    {
        curl_global_init(CURL_GLOBAL_DEFAULT);
    }

    HttpClient::~HttpClient()
    {
        curl_global_cleanup();
    }

    HttpClient::Response* HttpClient::OnRequest(Request* request)
    {
        curl_httppost* form = nullptr;
        curl_httppost* lastPointer = nullptr;
        const std::vector<KeyValue>& params = request->GetParams();
        for (std::vector<KeyValue>::const_iterator it = params.begin(); it != params.end(); it++)
        {
            curl_formadd(&form, &lastPointer,
                         CURLFORM_PTRNAME, (*it).first.CStr(),
                         CURLFORM_PTRCONTENTS, (*it).second.CStr(),
                         CURLFORM_END);
        }

        if (CURL* curl = curl_easy_init())
        {
            const char* method = request->GetMethod();
            if (method[0] == 'P' &&
                method[1] == 'O' &&
                method[2] == 'S' &&
                method[3] == 'T')
                curl_easy_setopt(curl, CURLOPT_POST, 1L);
            else if (method[0] == 'P' &&
                     method[1] == 'U' &&
                     method[2] == 'T')
                 curl_easy_setopt(curl, CURLOPT_PUT, 1L);

            curl_easy_setopt(curl, CURLOPT_URL, request->GetURL().CStr());
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 3L);
            curl_easy_setopt(curl, CURLOPT_USERAGENT, request->GetUserAgent().CStr());
            if (form)
                curl_easy_setopt(curl, CURLOPT_HTTPPOST, form);

            Header header;
            header.id = Header::ID;
            Body body;
            body.id = Body::ID;

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnRecv);
            curl_easy_setopt(curl, CURLOPT_WRITEHEADER, &header);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);

            CURLcode result = curl_easy_perform(curl);

            if (result != CURLE_OK)
            {
                long responseCode = 0;
                curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &responseCode);
                curl_easy_cleanup(curl);
                if (form)
                    curl_formfree(form);
                return new Response(request, static_cast<StatusCode>(responseCode));
            }

            curl_easy_cleanup(curl);

            if (form)
                curl_formfree(form);

            return new Response(request,
                                HttpClient::Ok,
                                String(&body.content[0], 0, body.content.size()),
                                header.contentType);
        }
        else
        {
            if (form)
                curl_formfree(form);
            
            return new Response(request, ClientError);
        }
    }
}