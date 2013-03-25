#include <Bibim/PCH.h>
#include <Bibim/HttpClient.Windows.h>
#include <Bibim/AutoLocker.h>
#include <Bibim/Environment.h>
#include <Bibim/Numerics.h>
#include <Bibim/Clock.h>
#include <Bibim/Stream.h>
#include <wininet.h>

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
        BOOL cracked = ::InternetCrackUrl(request->GetURL().CStr(), request->GetURL().GetLength(), ICU_ESCAPE, &urlComponents);
        if (cracked == FALSE)
            return new Response(request, ClientError, String::Empty);
        if (urlComponents.nScheme != INTERNET_SCHEME_HTTP)
            return new Response(request, ClientError, String::Empty);

        LocalHandles handles;

        handles.session = ::InternetOpen(request->GetUserAgent().CStr(),
                                         INTERNET_OPEN_TYPE_PRECONFIG,
                                         NULL, NULL, 0);
        if (handles.session == NULL)
            return new Response(request, ClientError, String::Empty);

        handles.connection = ::InternetConnect(handles.session,
                                               urlComponents.lpszHostName, urlComponents.nPort,
                                               NULL, NULL,
                                               INTERNET_SERVICE_HTTP, 0, NULL);
        if (handles.connection == NULL)
            return new Response(request, ClientError, String::Empty);

        const int urlPathAndExtraLength = urlComponents.dwUrlPathLength + urlComponents.dwExtraInfoLength;
        char* urlPathAndExtra = BBStackAlloc(char, urlPathAndExtraLength + 1);
        String::CopyChars(&urlPathAndExtra[0], urlComponents.lpszUrlPath);
        String::CopyChars(&urlPathAndExtra[urlComponents.dwUrlPathLength], urlComponents.lpszExtraInfo);
        urlPathAndExtra[urlPathAndExtraLength] = '\0';

        handles.request = ::HttpOpenRequest(handles.connection, request->GetMethod(), urlPathAndExtra,
                                            HTTP_VERSION, NULL, NULL,
                                            INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_NO_COOKIES,
                                            NULL);

        BBStackFree(urlPathAndExtra);
        if (handles.request == NULL)
            return new Response(request, ClientError, String::Empty);

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
            return new Response(request, ClientError, String::Empty);

        int contentLength = 0;
        if (request->GetParams().empty() == false)
        {
            const std::vector<KeyValue>& params = request->GetParams();
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
            return new Response(request, ClientError, String::Empty);

        char* content = nullptr;
        if (contentLength > 0)
        {
            const std::vector<KeyValue>& params = request->GetParams();
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
                return new Response(request, Timeout, String::Empty);
            else
                return new Response(request, ClientError, String::Empty);
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
            return new Response(request, statusCode, String::Empty);

        std::vector<byte> response;
        if (responseLength != Int::Max)
        {
            response.resize(responseLength);

            byte* responsePointer = &response[0];
            DWORD remainingSize = responseLength;

            static const DWORD DefaultTimeout = 10000;
            const DWORD startTime = ::GetTickCount();

            while (remainingSize > 0)
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
                    return new Response(request, Timeout, String::Empty);
            }
        }
        else
        {
            byte temporaryBuffer[4096 * 2];
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

        request->GetOutputStream()->Write(&response[0],
                                          response.size());

        return new Response(request,
                            statusCode,
                            contentType);
    }
}