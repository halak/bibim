#pragma once
#ifndef __BIBIM_HTTPCLIENT_EMSCRIPTEN_H__
#define __BIBIM_HTTPCLIENT_EMSCRIPTEN_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_PLATFORM_EMSCRIPTEN) || defined(BIBIM_PLATFORM_IOS))

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
    };
}

#endif
#endif