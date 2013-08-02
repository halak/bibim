#pragma once
#ifndef __BIBIM_PERFORMANCE_H__
#define __BIBIM_PERFORMANCE_H__

#include <Bibim/FWD.h>

namespace Bibim
{
    class Performance
    {
        BBThisIsStaticClass(Performance);
        public:
            static inline Stream* GetStream();
            static void SetStream(Stream* value);

        private:
            static StreamPtr stream;
    };

    Stream* Performance::GetStream()
    {
        return stream;
    }
}

#endif