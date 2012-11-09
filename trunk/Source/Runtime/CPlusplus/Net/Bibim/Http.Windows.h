#pragma once
#ifndef __BIBIM_HTTP_WINDOWS_H__
#define __BIBIM_HTTP_WINDOWS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class Http
        {
            BBThisIsStaticClass(Http);
            public:
                enum StatusCode
                {
                    Ok = 200,
                };

            public:
                void GET()  { }
                void POST() { }
        };
    }

#   include <Bibim/Http.Windows.inl>

#endif