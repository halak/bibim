#pragma once
#ifndef __BIBIM_HTTPCLIENT_CURL_H__
#define __BIBIM_HTTPCLIENT_CURL_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_PLATFORM_WINDOWS) || defined(BIBIM_PLATFORM_ANDROID) || defined(BIBIM_PLATFORM_IOS))

#include <Bibim/HttpClientBase.h>

namespace Bibim
{
    class HttpClient : public HttpClientBase
    {
        BBModuleClass(HttpClient, HttpClientBase, 'H', 'T', 'T', 'P');
        public:
            HttpClient();
            virtual ~HttpClient();

        private:
            virtual Response* OnRequest(Request* request);

            struct WithRequest
            {
                HttpClient* client;
                HttpClient::Request* request;
            };
            friend int OnProgress(WithRequest* thiz, double t, double d, double ultotal, double ulnow);
    };
}

#endif
#endif