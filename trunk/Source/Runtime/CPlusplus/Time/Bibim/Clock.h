#pragma once
#ifndef __BIBIM_CLOCK_H__
#define __BIBIM_CLOCK_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
        class Clock
        {
            BBThisIsStaticClass(Clock);
            public:
                static float GetCurrent();
                static int  GetCurrentMilliSeconds();
                static bool IsHighResolution();
        };
    }

#endif