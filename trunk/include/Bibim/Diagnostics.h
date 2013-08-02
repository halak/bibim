#pragma once
#ifndef __BIBIM_DIAGNOSTICS_H__
#define __BIBIM_DIAGNOSTICS_H__

#include <Bibim/FWD.h>

namespace Bibim
{
    class Diagnostics
    {
        BBThisIsStaticClass(Diagnostics);
        public:
            enum ProtocolID
            {
                LogProtocolID = 10001,
                PerformanceProtocolID = 11001,
            };

            static inline Stream* GetStream();
            static void SetStream(Stream* value);

        private:
            static StreamPtr stream;
    };

    Stream* Diagnostics::GetStream()
    {
        return stream;
    }
}

#endif