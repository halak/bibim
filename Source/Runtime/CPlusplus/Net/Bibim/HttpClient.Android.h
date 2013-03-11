#pragma once
#ifndef __BIBIM_HTTPCLIENT_ANDROID_H__
#define __BIBIM_HTTPCLIENT_ANDROID_H__

#   include <Bibim/FWD.h>
#   include <Bibim/HttpClientBase.h>

    namespace Bibim
    {
        class HttpClient : public HttpClientBase
        {
            BBModuleClass(HttpClient, HttpClientBase, 'H', 'T', 'T', 'P');
            public:
                HttpClient();
                virtual ~HttpClient();

            public:
                static void SetJNIEnv(void* value);

            private:
                virtual Response* OnRequest(Request* request);
        };
    }

#   include <Bibim/HttpClient.Android.inl>

#endif