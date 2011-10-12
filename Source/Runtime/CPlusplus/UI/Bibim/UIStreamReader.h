#pragma once
#ifndef __BIBIM_UISTREAMREADER_H__
#define __BIBIM_UISTREAMREADER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/BinaryReader.h>

    namespace Bibim
    {
        class UIStreamReader : public BinaryReader
        {
            public:
                UIStreamReader(Stream* sourceStream);
                ~UIStreamReader();
        };
    }

#endif