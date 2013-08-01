#pragma once
#ifndef __BIBIM_CRASHDUMP_H__
#define __BIBIM_CRASHDUMP_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class CrashDump
        {
            BBThisIsStaticClass(CrashDump);
            private:
                friend class Startup;
                static void Initialize();
        };
    }

#endif