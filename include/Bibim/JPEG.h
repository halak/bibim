#pragma once
#ifndef __BIBIM_JPEG_H__
#define __BIBIM_JPEG_H__

#include <Bibim/FWD.h>

namespace Bibim
{
    class JPEG
    {
        BBThisIsStaticClass(JPEG);
        public:
            static bool Read(AssetStreamReader& reader,
                             byte* destination,
                             int destinationPitch,
                             bool swapRedBlue);
    };
}

#endif