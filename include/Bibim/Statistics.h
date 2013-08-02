#pragma once
#ifndef __BIBIM_STATISTICS_H__
#define __BIBIM_STATISTICS_H__

#include <Bibim/FWD.h>

namespace Bibim
{
    class Statistics
    {
        BBThisIsStaticClass(Statistics);
        public:
            static inline Stream* GetStream();
            static void SetStream(Stream* value);

        private:
            static StreamPtr stream;
    };

    Stream* Statistics::GetStream()
    {
        return stream;
    }
}

#endif