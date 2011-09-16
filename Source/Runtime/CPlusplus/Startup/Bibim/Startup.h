#pragma once
#ifndef __BIBIM_STARTUP_H__
#define __BIBIM_STARTUP_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
        class Startup
        {
            BBThisIsStaticClass(Startup);
            public:
                static void All();
        };
    }

#endif