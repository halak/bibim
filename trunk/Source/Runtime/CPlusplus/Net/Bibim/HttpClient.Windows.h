#pragma once
#ifndef __BIBIM_HTTPCLIENT_WINDOWS_H__
#define __BIBIM_HTTPCLIENT_WINDOWS_H__

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
        class HttpClient : public TimelineGameModule
        {
            BBModuleClass(HttpClient, TimelineGameModule, 'H', 'T', 'T', 'P');
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
                HttpClient();
                virtual ~HttpClient();

                virtual void Update(float dt, int timestamp);

                void GET(const String& url, Callback* callback);
                void GET(const String& url, const std::vector<KeyValue>& params, Callback* callback);
                void GET(const String& url, const std::map<String, String>& params, Callback* callback);
                void POST(const String& url, Callback* callback);
                void POST(const String& url, const std::vector<KeyValue>& params, Callback* callback);
                void POST(const String& url, const std::map<String, String>& params, Callback* callback);

                inline const String& GetUserAgent() const;
                inline void SetUserAgent(const String& value);

            private:
                void DoRequest(const char* method, const String& url, std::vector<KeyValue>& params, Callback* callback);

                class Request
                {
                    BBThisIsNoncopyableClass(Request);
                    public:
                        Request(const char* method, const String& url,
                                std::vector<KeyValue>& params,
                                const String& userAgent,
                                Callback* callback);
                        ~Request();

                        void Run(HttpClient* client);

                    private:
                        const char* method;
                        String url;
                        std::vector<KeyValue> params;
                        String userAgent;
                        CallbackPtr callback;
                };

                class Response
                {
                    BBThisIsNoncopyableClass(Response);
                    public:
                        Response(StatusCode statusCode, Callback* callback);
                        Response(StatusCode statusCode, const String& content, const String& contentType, Callback* callback);
                        ~Response();

                        void Invoke();

                    private:
                        StatusCode statusCode;
                        String content;
                        String contentType;
                        CallbackPtr callback;
                };

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
                        HttpClient* Client;

                    protected:
                        virtual void OnWork();

                    private:
                        RequestQueue requestQueue;
                        Lock requestQueueLock;
                        bool closed;
                };

                void OnResponse(Response* response);

                static StatusCode NormalizeStatusCode(int statusCode);

            private:
                RequestThread requestThread;
                ResponseCollection responses;
                Lock responsesLock;

                String userAgent;
        };
    }

#   include <Bibim/HttpClient.Windows.inl>

#endif