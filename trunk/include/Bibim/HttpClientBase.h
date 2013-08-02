#pragma once
#ifndef __BIBIM_HTTPCLIENT_BASE_H__
#define __BIBIM_HTTPCLIENT_BASE_H__

#include <Bibim/FWD.h>
#include <Bibim/TimelineGameModule.h>
#include <Bibim/Lock.h>
#include <Bibim/String.h>
#include <Bibim/Thread.h>
#include <deque>
#include <map>
#include <vector>

namespace Bibim
{
    class HttpClientBase : public TimelineGameModule
    {
        BBAbstractModuleClass(HttpClientBase, TimelineGameModule);
        public:
            typedef std::pair<String, String> KeyValue;

            enum StatusCode
            {
                ClientError = 0,
                Unknown = 1,
                Ok = 200,
                BadRequest = 400,
                NotFound = 404,
                Timeout = 408,
                ServerError = 500,
            };

            class Callback : public SharedObject
            {
                public:
                    virtual ~Callback() { }

                    virtual void OnProgress(const String& url, int current, int total) = 0;
                    virtual void OnResponse(const String& url, StatusCode statusCode, Stream* outputStream, const String& contentType) = 0;
            };
            typedef SharedPointer<Callback> CallbackPtr;

        public:
            HttpClientBase();
            virtual ~HttpClientBase();

            virtual void Update(float dt, int timestamp);

            void GET(const String& url, Stream* outputStream, Callback* callback);
            void GET(const String& url, const std::vector<KeyValue>& params, Stream* outputStream, Callback* callback);
            void GET(const String& url, const std::map<String, String>& params, Stream* outputStream, Callback* callback);
            void POST(const String& url, Stream* outputStream, Callback* callback);
            void POST(const String& url, const std::vector<KeyValue>& params, Stream* outputStream, Callback* callback);
            void POST(const String& url, const std::map<String, String>& params, Stream* outputStream, Callback* callback);

            inline const String& GetUserAgent() const;
            inline void SetUserAgent(const String& value);

        protected:
            class Response;
            class Request
            {
                BBThisIsNoncopyableClass(Request);
                public:
                    Request(const char* method, const String& url,
                            std::vector<KeyValue>& params,
                            const String& userAgent,
                            Stream* outputStream,
                            Callback* callback);
                    ~Request();

                    inline const char* GetMethod() const;
                    inline const String& GetURL() const;
                    inline const std::vector<KeyValue>& GetParams() const;
                    inline const String& GetUserAgent() const;
                    inline Stream* GetOutputStream() const;

                private:
                    const char* method;
                    String url;
                    std::vector<KeyValue> params;
                    String userAgent;
                    StreamPtr outputStream;
                    CallbackPtr callback;

                    friend class HttpClientBase;
                    friend class Response;
            };

            class Response
            {
                BBThisIsNoncopyableClass(Response);
                public:
                    Response(Request* request, StatusCode statusCode, const String& contentType);
                    ~Response();

                    void Invoke();

                private:
                    String url;
                    StatusCode statusCode;
                    std::vector<byte> content;
                    String contentType;
                    StreamPtr outputStream;
                    CallbackPtr callback;
            };

            virtual Response* OnRequest(Request* request) = 0;
            static StatusCode NormalizeStatusCode(int statusCode);

            void AddProgress(Request* request, int current, int total);

        private:
            void DoRequest(const char* method, const String& url, std::vector<KeyValue>& params, Stream* outputStream, Callback* callback);
            void AddResponse(Response* response);

            typedef std::deque<Request*> RequestQueue;
            typedef std::vector<Response*> ResponseCollection;

            class RequestThread : public Thread
            {
                public:
                    RequestThread();
                    virtual ~RequestThread();

                    void Add(Request* request);

                    void RequestClose();

                public:
                    HttpClientBase* Client;

                protected:
                    virtual void OnWork();

                private:
                    RequestQueue requestQueue;
                    Lock requestQueueLock;
                    bool closed;
            };

            struct Progress
            {
                String url;
                int current;
                int total;
                Callback* callback;
            };

        private:
            RequestThread requestThread;
            ResponseCollection responses;
            Lock responsesLock;

            std::vector<Progress> progresses;
            Lock progressesLock;

            String userAgent;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const String& HttpClientBase::GetUserAgent() const
    {
        return userAgent;
    }

    void HttpClientBase::SetUserAgent(const String& value)
    {
        userAgent = value;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const char* HttpClientBase::Request::GetMethod() const
    {
        return method;
    }

    const String& HttpClientBase::Request::GetURL() const
    {
        return url;
    }

    const std::vector<HttpClientBase::KeyValue>& HttpClientBase::Request::GetParams() const
    {
        return params;
    }

    const String& HttpClientBase::Request::GetUserAgent() const
    {
        return userAgent;
    }

    Stream* HttpClientBase::Request::GetOutputStream() const
    {
        return outputStream;
    }
}

#endif