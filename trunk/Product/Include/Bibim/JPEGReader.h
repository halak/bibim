#pragma once
#ifndef __BIBIM_JPEGREADER_H__
#define __BIBIM_JPEGREADER_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class JPEGReader
        {
            BBThisIsStaticClass(JPEGReader);
            public:
                static bool Read(AssetStreamReader& reader,
                                 byte* destination,
                                 int destinationPitch,
                                 bool swapRedBlue);
        };
    }

#endif