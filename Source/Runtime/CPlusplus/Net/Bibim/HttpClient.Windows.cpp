#include <Bibim/PCH.h>
#include <Bibim/HttpClient.Windows.h>
#include <Bibim/AutoLocker.h>
#include <Bibim/Environment.h>
#include <Bibim/Numerics.h>
#include <Bibim/Clock.h>
#include <wininet.h>

namespace Bibim
{
    HttpClient::HttpClient()
    {
        requestThread.Client = this;
    }

    HttpClient::~HttpClient()
    {
        requestThread.RequestClose();
        requestThread.Join();

        ResponseCollection temporaryResponses;
        responses.swap(temporaryResponses);

        for (ResponseCollection::const_iterator it = temporaryResponses.begin(); it != temporaryResponses.end(); it++)
            delete (*it);
    }

    void HttpClient::Update(float /*dt*/, int /*timestamp*/)
    {
        if (responses.size() == 0)
            return;

        ResponseCollection temporaryResponses;
        {
            BBAutoLock(responsesLock);
            responses.swap(temporaryResponses);
        }

        for (ResponseCollection::const_iterator it = temporaryResponses.begin(); it != temporaryResponses.end(); it++)
        {
            (*it)->Invoke();
            delete (*it);
        }
    }

    void HttpClient::GET(const String& url, Callback* callback)
    {
        std::vector<KeyValue> v;
        DoRequest("GET", url, v, callback);
    }

    void HttpClient::GET(const String& url, const std::vector<KeyValue>& params, Callback* callback)
    {
        std::vector<KeyValue> v;
        v.reserve(params.size());
        for (std::vector<KeyValue>::const_iterator it = params.begin(); it != params.end(); it++)
        {
            if ((*it).first.IsEmpty() == false)
                v.push_back(*it);
        }
        DoRequest("GET", url, v, callback);
    }

    void HttpClient::GET(const String& url, const std::map<String, String>& params, Callback* callback)
    {
        std::vector<KeyValue> v;
        for (std::map<String, String>::const_iterator it = params.begin(); it != params.end(); it++)
        {
            if ((*it).first.IsEmpty() == false)
                v.push_back(*it);
        }
        DoRequest("GET", url, v, callback);
    }

    void HttpClient::POST(const String& url, Callback* callback)
    {
        std::vector<KeyValue> v;
        DoRequest("POST", url, v, callback);
    }

    void HttpClient::POST(const String& url, const std::vector<KeyValue>& params, Callback* callback)
    {
        std::vector<KeyValue> v;
        v.reserve(params.size());
        for (std::vector<KeyValue>::const_iterator it = params.begin(); it != params.end(); it++)
        {
            if ((*it).first.IsEmpty() == false)
                v.push_back(*it);
        }
        DoRequest("POST", url, v, callback);
    }

    void HttpClient::POST(const String& url, const std::map<String, String>& params, Callback* callback)
    {
        std::vector<KeyValue> v;
        for (std::map<String, String>::const_iterator it = params.begin(); it != params.end(); it++)
        {
            if ((*it).first.IsEmpty() == false)
                v.push_back(*it);
        }
        DoRequest("POST", url, v, callback);
    }

    void HttpClient::DoRequest(const char* method, const String& url, std::vector<KeyValue>& params, Callback* callback)
    {
        requestThread.Add(new Request(method, url, params, userAgent, callback));
    }

    void HttpClient::OnResponse(Response* response)
    {
        BBAutoLock(responsesLock);
        responses.push_back(response);
    }

    HttpClient::StatusCode HttpClient::NormalizeStatusCode(int statusCode)
    {
        if (200 <= statusCode && statusCode < 300)
            return Ok;
        else if (300 <= statusCode && statusCode < 400)
            return Unknown;
        else if (400 <= statusCode && statusCode < 500)
        {
            if (statusCode == 404)
                return NotFound;
            else if (statusCode == 408)
                return Timeout;
            else
                return BadRequest;
        }
        else if (500 <= statusCode && statusCode < 600)
            return ServerError;
        else
            return Unknown;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    HttpClient::Request::Request(const char* method, const String& url, std::vector<KeyValue>& params, const String& userAgent, Callback* callback)
        : method(method),
          url(url),
          userAgent(userAgent),
          callback(callback)
    {
        this->params.swap(params);
    }

    HttpClient::Request::~Request()
    {
    }

    void HttpClient::Request::Run(HttpClient* client)
    {
        struct LocalHandles
        {
            HINTERNET session;
            HINTERNET connection;
            HINTERNET request;

            LocalHandles()
                : session(NULL),
                  connection(NULL),
                  request(NULL)
            {
            }

            ~LocalHandles()
            {
                if (request)
                    ::InternetCloseHandle(request);
                if (connection)
                    ::InternetCloseHandle(connection);
                if (session)
                    ::InternetCloseHandle(session);
            }
        };

        char scheme[INTERNET_MAX_SCHEME_LENGTH + 1];
        char hostName[INTERNET_MAX_HOST_NAME_LENGTH + 1];
        char urlPath[INTERNET_MAX_PATH_LENGTH + 1];
        char urlExtra[INTERNET_MAX_PATH_LENGTH + 1];
        URL_COMPONENTS urlComponents;
        urlComponents.dwStructSize = sizeof(urlComponents);
        urlComponents.lpszScheme = scheme;
        urlComponents.dwSchemeLength = sizeof(scheme) / sizeof(scheme[0]);
        urlComponents.nScheme = INTERNET_SCHEME_HTTP;
        urlComponents.lpszHostName = hostName;
        urlComponents.dwHostNameLength = sizeof(hostName) / sizeof(hostName[0]);
        urlComponents.nPort = INTERNET_DEFAULT_HTTP_PORT;
        urlComponents.lpszUserName = NULL;
        urlComponents.dwUserNameLength = 0;
        urlComponents.lpszPassword = NULL;
        urlComponents.dwPasswordLength = 0;
        urlComponents.lpszUrlPath = urlPath;
        urlComponents.dwUrlPathLength = sizeof(urlPath) / sizeof(urlPath[0]);
        urlComponents.lpszExtraInfo = urlExtra;
        urlComponents.dwExtraInfoLength = sizeof(urlExtra) / sizeof(urlExtra[0]);
        BOOL cracked = ::InternetCrackUrl(url.CStr(), url.GetLength(), ICU_ESCAPE, &urlComponents);
        if (cracked == FALSE)
            return client->OnResponse(new Response(ClientError, callback));
        if (urlComponents.nScheme != INTERNET_SCHEME_HTTP)
            return client->OnResponse(new Response(ClientError, callback));

        LocalHandles handles;

        handles.session = ::InternetOpen(client->GetUserAgent().CStr(),
                                         INTERNET_OPEN_TYPE_PRECONFIG,
                                         NULL, NULL, 0);
        if (handles.session == NULL)
            return client->OnResponse(new Response(ClientError, callback));

        handles.connection = ::InternetConnect(handles.session,
                                               urlComponents.lpszHostName, urlComponents.nPort,
                                               NULL, NULL,
                                               INTERNET_SERVICE_HTTP, 0, NULL);
        if (handles.connection == NULL)
            return client->OnResponse(new Response(ClientError, callback));

        const int urlPathAndExtraLength = urlComponents.dwUrlPathLength + urlComponents.dwExtraInfoLength;
        char* urlPathAndExtra = BBStackAlloc(char, urlPathAndExtraLength + 1);
        String::CopyChars(&urlPathAndExtra[0], urlComponents.lpszUrlPath);
        String::CopyChars(&urlPathAndExtra[urlComponents.dwUrlPathLength], urlComponents.lpszExtraInfo);
        urlPathAndExtra[urlPathAndExtraLength] = '\0';

        handles.request = ::HttpOpenRequest(handles.connection, method, urlPathAndExtra,
                                            HTTP_VERSION, NULL, NULL,
                                            INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_NO_COOKIES,
                                            NULL);

        BBStackFree(urlPathAndExtra);
        if (handles.request == NULL)
            return client->OnResponse(new Response(ClientError, callback));

        BOOL result = TRUE;

        DWORD securityOptions = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
                                SECURITY_FLAG_IGNORE_REVOCATION |
                                SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP |
                                SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS |
                                SECURITY_FLAG_IGNORE_CERT_DATE_INVALID |
                                SECURITY_FLAG_IGNORE_CERT_CN_INVALID;
        result = ::InternetSetOption(handles.request, INTERNET_OPTION_SECURITY_FLAGS,
                                     &securityOptions, sizeof(securityOptions));
        if (result == FALSE)
            return client->OnResponse(new Response(ClientError, callback));

        int contentLength = 0;
        if (params.empty() == false)
        {
            for (std::vector<KeyValue>::const_iterator it = params.begin(); it != params.end(); it++)
            {
                contentLength += (*it).first.GetLength();
                contentLength += 1; // =
                contentLength += (*it).second.GetLength();
                contentLength += 1; // &
            }
            contentLength -= 1; // &
        }

        char header[256];
        int headerIndex = 0;
        headerIndex += String::CopyChars(&header[headerIndex], "Accept: text/*,application/*\r\n");
        headerIndex += String::CopyChars(&header[headerIndex], "Accept-Charset: UTF-8\r\n");
        headerIndex += String::CopyChars(&header[headerIndex], "Accept-Language: ");
        headerIndex += String::CopyChars(&header[headerIndex], Environment::GetLocaleName().CStr());
        headerIndex += String::CopyChars(&header[headerIndex], "\r\n");
        headerIndex += String::CopyChars(&header[headerIndex], "Content-Type: application/x-www-form-urlencoded\r\n");
        headerIndex += String::CopyChars(&header[headerIndex], "Content-Length: ");
        headerIndex += String::CopyChars(&header[headerIndex], Int::ToString(contentLength).CStr());
        headerIndex += String::CopyChars(&header[headerIndex], "\r\n");
        header[headerIndex] = '\0';

        result = ::HttpAddRequestHeaders(handles.request, header, headerIndex,
                                         HTTP_ADDREQ_FLAG_ADD);
        if (result == FALSE)
            return client->OnResponse(new Response(ClientError, callback));

        char* content = nullptr;
        if (contentLength > 0)
        {
            content = BBStackAlloc(char, contentLength + 1);
            int contentIndex = 0;
            for (std::vector<KeyValue>::const_iterator it = params.begin(); it != params.end(); it++)
            {
                contentIndex += String::CopyChars(&content[contentIndex], (*it).first.CStr());
                content[contentIndex++] = '=';
                contentIndex += String::CopyChars(&content[contentIndex], (*it).second.CStr());
                content[contentIndex++] = '&';
            }
            content[contentLength] = '\0';
            BBAssert(contentIndex == contentLength + 1);
        }

        result = ::HttpSendRequest(handles.request, NULL, 0, content, contentLength);
        if (content)
            BBStackFree(content);
        if (result == FALSE)
        {
            const DWORD errorCode = ::GetLastError();
            if (errorCode == ERROR_INTERNET_TIMEOUT)
                return client->OnResponse(new Response(Timeout, callback));
            else
                return client->OnResponse(new Response(ClientError, callback));
        }

        DWORD querySize = 0;
        DWORD queryStatusCode = 0;
        DWORD queryContentLength = 0;

        querySize = sizeof(DWORD);
        result = ::HttpQueryInfo(handles.request, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
                                 &queryStatusCode, &querySize, NULL);
        if (result == FALSE)
            queryStatusCode = HTTP_STATUS_NO_CONTENT;

        querySize = sizeof(DWORD);
        result = ::HttpQueryInfo(handles.request, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER,
                                 &queryContentLength, &querySize, NULL);
        if (result == FALSE)
        {
            if (GetLastError() == ERROR_HTTP_HEADER_NOT_FOUND)
                queryContentLength = Int::Max;
            else
                queryContentLength = 0;
        }

        char contentType[64] = { '\0', };
        querySize = sizeof(contentType);
        result = ::HttpQueryInfo(handles.request, HTTP_QUERY_CONTENT_TYPE,
                                 contentType, &querySize, NULL);
        if (result)
            contentType[querySize] = '\0';
        else
            String::CopyChars(contentType, "");

        const StatusCode statusCode = NormalizeStatusCode(queryStatusCode);
        const int responseLength = queryContentLength;

        if (responseLength == 0)
            return client->OnResponse(new Response(statusCode, callback));

        std::vector<char> response;
        if (responseLength != Int::Max)
        {
            response.resize(responseLength + 1);
            response.back() = '\0';

            char* responsePointer = &response[0];
            const char* responseBufferEnd = &response[responseLength];
            DWORD remainingSize = responseLength;

            static const DWORD DefaultTimeout = 10000;
            const DWORD startTime = ::GetTickCount();

            while (responsePointer != responseBufferEnd)
            {
                DWORD readSize = 0;
                if (::InternetReadFile(handles.request, responsePointer, remainingSize, &readSize))
                {
                    responsePointer += readSize;
                    remainingSize -= readSize;
                }
                else
                    Thread::Sleep(10);

                if (::GetTickCount() - startTime >= DefaultTimeout)
                    return client->OnResponse(new Response(Timeout, callback));
            }
        }
        else
        {
            char temporaryBuffer[4096 * 2];
            for (;;)
            {
                DWORD readSize = 0;
                if (::InternetReadFile(handles.request, temporaryBuffer, sizeof(temporaryBuffer), &readSize))
                {
                    if (readSize == 0)
                        break;

                    response.insert(response.end(),
                                    &temporaryBuffer[0],
                                    &temporaryBuffer[readSize]);
                }
                else
                    break;
            }
        }

        client->OnResponse(new Response(statusCode,
                                        String(&response[0], 0, response.size()),
                                        contentType,
                                        callback));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    HttpClient::Response::Response(StatusCode statusCode, Callback* callback)
        : statusCode(statusCode),
          callback(callback)
    {
    }

    HttpClient::Response::Response(StatusCode statusCode, const String& content, const String& contentType, Callback* callback)
        : statusCode(statusCode),
          content(content),
          contentType(contentType),
          callback(callback)
    {
    }

    HttpClient::Response::~Response()
    {
    }

    void HttpClient::Response::Invoke()
    {
        callback->OnResponse(statusCode, content, contentType);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    HttpClient::RequestThread::RequestThread()
        : closed(false)
    {
    }

    HttpClient::RequestThread::~RequestThread()
    {
        RequestQueue temporaryRequests;
        {
            BBAutoLock(requestQueueLock);
            requestQueue.swap(temporaryRequests);
        }

        for (RequestQueue::iterator it = temporaryRequests.begin(); it != temporaryRequests.end(); it++)
            delete (*it);
    }

    void HttpClient::RequestThread::Add(Request* request)
    {
        BBAutoLock(requestQueueLock);
        requestQueue.push_back(request);
    }

    void HttpClient::RequestThread::RequestClose()
    {
        closed = true;
    }

    void HttpClient::RequestThread::OnWork()
    {
        while (closed == false)
        {
            if (requestQueue.empty() == false)
            {
                Request* request = nullptr;
                {
                    BBAutoLock(requestQueueLock);
                    request = requestQueue.front();
                    requestQueue.pop_front();
                }

                request->Run(Client);

                delete request;
            }

            Thread::Sleep(100);
        }
    }
}