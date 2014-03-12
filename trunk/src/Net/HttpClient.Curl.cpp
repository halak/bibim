#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_WINDOWS) || defined(BIBIM_PLATFORM_ANDROID) || defined(BIBIM_PLATFORM_IOS))

#include <Bibim/HttpClient.Curl.h>
#include <Bibim/Stream.h>

#ifndef CURL_STATICLIB
#define CURL_STATICLIB
#endif
#include <curl/curl.h>

namespace Bibim
{
    namespace
    {
        struct Data
        {
            int id;
        };

        struct Header : public Data
        {
            static const int ID = 0;
            String contentType;
        };

        struct Body : Data
        {
            static const int ID = 1;
            Stream* stream;
        };

        static size_t OnRecv(void* ptr, size_t size, size_t nmemb, void* stream)
        {
            switch (reinterpret_cast<Data*>(stream)->id)
            {
                case Header::ID:
                    {
                        static const String contentTypeKey = "Content-Type:";

                        Header* header = reinterpret_cast<Header*>(stream);
                        String headerItem = String(reinterpret_cast<const char*>(ptr), 0, size * nmemb);
                        if (headerItem.StartsWith(contentTypeKey))
                            header->contentType = headerItem.Substring(contentTypeKey.GetLength());
                    }
                    return nmemb;
                case Body::ID:
                    {
                        Body* body = reinterpret_cast<Body*>(stream);
                        body->stream->Write(ptr, size * nmemb);
                    }
                    return nmemb;
                default:
                    return 0;
            }
        }
    }

    // HttpClient friend function
    int OnProgress(HttpClient::WithRequest* thiz, 
                   double t, /* dltotal */ 
                   double d, /* dlnow */ 
                   double /*ultotal*/,
                   double /*ulnow*/)
    {
        thiz->client->AddProgress(thiz->request, static_cast<int>(d), static_cast<int>(t));
        return 0;
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
        for (std::vector<KeyValue>::const_iterator it = params.begin(); it != params.end(); ++it)
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

            HttpClient::WithRequest o;
            o.client = this;
            o.request = request;

            curl_easy_setopt(curl, CURLOPT_URL, request->GetURL().CStr());
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
            curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, &OnProgress);
            curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &o);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 3L);
            curl_easy_setopt(curl, CURLOPT_USERAGENT, request->GetUserAgent().CStr());
            if (form)
                curl_easy_setopt(curl, CURLOPT_HTTPPOST, form);

            Header header;
            header.id = Header::ID;
            Body body;
            body.id = Body::ID;
            body.stream = request->GetOutputStream();

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &OnRecv);
            curl_easy_setopt(curl, CURLOPT_WRITEHEADER, &header);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);

            CURLcode result = curl_easy_perform(curl);

            long responseCode = 0;
            curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &responseCode);

            curl_easy_cleanup(curl);

            if (form)
                curl_formfree(form);

            String contentType;
            if (result == CURLE_OK)
                contentType = header.contentType;
            else
                contentType = String::Empty;

            return new Response(request,
                                static_cast<StatusCode>(responseCode),
                                contentType);
        }
        else
        {
            if (form)
                curl_formfree(form);
            
            return new Response(request, ClientError, String::Empty);
        }
    }
}
#endif