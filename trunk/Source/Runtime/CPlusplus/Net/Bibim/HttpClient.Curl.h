#pragma once
#ifndef __BIBIM_HTTPCLIENT_CURL_H__
#define __BIBIM_HTTPCLIENT_CURL_H__

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

            private:
                virtual Response* OnRequest(Request* request);
        };
    }

#   include <Bibim/HttpClient.Curl.inl>

#endif