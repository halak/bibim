#pragma once
#ifndef __BIBIM_PNGREADER_H__
#define __BIBIM_PNGREADER_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class PNGReader
        {
            BBThisIsStaticClass(PNGReader);
            public:
                static bool Read(AssetStreamReader& reader, byte* destination, int destinationPitch);
        };
    }

#endif