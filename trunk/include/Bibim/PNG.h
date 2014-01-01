#pragma once
#ifndef __BIBIM_PNG_H__
#define __BIBIM_PNG_H__

#include <Bibim/FWD.h>

namespace Bibim
{
    class PNG
    {
        BBThisIsStaticClass(PNG);
        public:
            static bool Read(AssetStreamReader& reader,
                             byte* destination,
                             int destinationPitch,
                             bool swapRedBlue);
    };
}

#endif