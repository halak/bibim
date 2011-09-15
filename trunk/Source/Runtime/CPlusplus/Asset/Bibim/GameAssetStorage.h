#pragma once
#ifndef __BIBIM_GAMEASSETSTORAGE_H__
#define __BIBIM_GAMEASSETSTORAGE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>

    namespace Bibim
    {
        class GameAssetStorage : public GameModule
        {
            public:
                GameAssetStorage();
                virtual ~GameAssetStorage();

            private:
        };
    }

#endif