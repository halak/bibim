#include <Bibim/PCH.h>
#include <Bibim/HttpClientBase.h>
#include <Bibim/AutoLocker.h>
#include <Bibim/Environment.h>
#include <Bibim/Numerics.h>
#include <Bibim/Clock.h>

namespace Bibim
{
    HttpClientBase::HttpClientBase()
    {
        requestThread.Client = this;
    }

    HttpClientBase::~HttpClientBase()
    {
        requestThread.RequestClose();
        requestThread.Join();

        ResponseCollection temporaryResponses;
        responses.swap(temporaryResponses);

        for (ResponseCollection::const_iterator it = temporaryResponses.begin(); it != temporaryResponses.end(); it++)
            delete (*it);
    }

    void HttpClientBase::Update(float /*dt*/, int /*timestamp*/)
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

    void HttpClientBase::GET(const String& url, Callback* callback)
    {
        std::vector<KeyValue> v;
        DoRequest("GET", url, v, callback);
    }

    void HttpClientBase::GET(const String& url, const std::vector<KeyValue>& params, Callback* callback)
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

    void HttpClientBase::GET(const String& url, const std::map<String, String>& params, Callback* callback)
    {
        std::vector<KeyValue> v;
        for (std::map<String, String>::const_iterator it = params.begin(); it != params.end(); it++)
        {
            if ((*it).first.IsEmpty() == false)
                v.push_back(*it);
        }
        DoRequest("GET", url, v, callback);
    }

    void HttpClientBase::POST(const String& url, Callback* callback)
    {
        std::vector<KeyValue> v;
        DoRequest("POST", url, v, callback);
    }

    void HttpClientBase::POST(const String& url, const std::vector<KeyValue>& params, Callback* callback)
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

    void HttpClientBase::POST(const String& url, const std::map<String, String>& params, Callback* callback)
    {
        std::vector<KeyValue> v;
        for (std::map<String, String>::const_iterator it = params.begin(); it != params.end(); it++)
        {
            if ((*it).first.IsEmpty() == false)
                v.push_back(*it);
        }
        DoRequest("POST", url, v, callback);
    }

    void HttpClientBase::DoRequest(const char* method, const String& url, std::vector<KeyValue>& params, Callback* callback)
    {
        requestThread.Add(new Request(method, url, params, userAgent, callback));
    }

    void HttpClientBase::AddResponse(Response* response)
    {
        BBAutoLock(responsesLock);
        responses.push_back(response);
    }

    HttpClientBase::StatusCode HttpClientBase::NormalizeStatusCode(int statusCode)
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

    HttpClientBase::Request::Request(const char* method, const String& url, std::vector<KeyValue>& params, const String& userAgent, Callback* callback)
        : method(method),
          url(url),
          userAgent(userAgent),
          callback(callback)
    {
        this->params.swap(params);
    }

    HttpClientBase::Request::~Request()
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    HttpClientBase::Response::Response(Request* request, StatusCode statusCode)
        : statusCode(statusCode),
          callback(request->callback)
    {
    }

    HttpClientBase::Response::Response(Request* request, StatusCode statusCode, const String& content, const String& contentType)
        : statusCode(statusCode),
          content(content),
          contentType(contentType),
          callback(request->callback)
    {
    }

    HttpClientBase::Response::~Response()
    {
    }

    void HttpClientBase::Response::Invoke()
    {
        callback->OnResponse(statusCode, content, contentType);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    HttpClientBase::RequestThread::RequestThread()
        : closed(false)
    {
        Start();
    }

    HttpClientBase::RequestThread::~RequestThread()
    {
        RequestQueue temporaryRequests;
        {
            BBAutoLock(requestQueueLock);
            requestQueue.swap(temporaryRequests);
        }

        for (RequestQueue::iterator it = temporaryRequests.begin(); it != temporaryRequests.end(); it++)
            delete (*it);
    }

    void HttpClientBase::RequestThread::Add(Request* request)
    {
        BBAutoLock(requestQueueLock);
        requestQueue.push_back(request);
    }

    void HttpClientBase::RequestThread::RequestClose()
    {
        closed = true;
    }

    void HttpClientBase::RequestThread::OnWork()
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

                if (Response* response = Client->OnRequest(request))
                    Client->AddResponse(response);

                delete request;
            }
            else
                Thread::Sleep(100);
        }
    }
}