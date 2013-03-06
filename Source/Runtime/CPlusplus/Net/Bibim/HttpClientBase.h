#pragma once
#ifndef __BIBIM_HTTPCLIENT_BASE_H__
#define __BIBIM_HTTPCLIENT_BASE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/TimelineGameModule.h>
#   include <Bibim/Lock.h>
#   include <Bibim/String.h>
#   include <Bibim/Thread.h>
#   include <deque>
#   include <map>
#   include <vector>

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

                        virtual void OnResponse(StatusCode statusCode, const String& content, const String& contentType) = 0;
                };
                typedef SharedPointer<Callback> CallbackPtr;

            public:
                HttpClientBase();
                virtual ~HttpClientBase();

                virtual void Update(float dt, int timestamp);

                void GET(const String& url, Callback* callback);
                void GET(const String& url, const std::vector<KeyValue>& params, Callback* callback);
                void GET(const String& url, const std::map<String, String>& params, Callback* callback);
                void POST(const String& url, Callback* callback);
                void POST(const String& url, const std::vector<KeyValue>& params, Callback* callback);
                void POST(const String& url, const std::map<String, String>& params, Callback* callback);

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
                                Callback* callback);
                        ~Request();

                        inline const char* GetMethod() const;
                        inline const String& GetURL() const;
                        inline const std::vector<KeyValue>& GetParams() const;
                        inline const String& GetUserAgent() const;

                    private:
                        const char* method;
                        String url;
                        std::vector<KeyValue> params;
                        String userAgent;
                        CallbackPtr callback;

                        friend class Response;
                };

                class Response
                {
                    BBThisIsNoncopyableClass(Response);
                    public:
                        Response(Request* request, StatusCode statusCode);
                        Response(Request* request, StatusCode statusCode, const String& content, const String& contentType);
                        ~Response();

                        void Invoke();

                    private:
                        StatusCode statusCode;
                        String content;
                        String contentType;
                        CallbackPtr callback;
                };

                virtual Response* OnRequest(Request* request) = 0;
                static StatusCode NormalizeStatusCode(int statusCode);

            private:
                void DoRequest(const char* method, const String& url, std::vector<KeyValue>& params, Callback* callback);
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

            private:
                RequestThread requestThread;
                ResponseCollection responses;
                Lock responsesLock;

                String userAgent;
        };
    }

#   include <Bibim/HttpClientBase.inl>

#endif