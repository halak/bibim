#pragma once
#ifndef __BIBIM_GAMEASSETLOADINGTASK_H__
#define __BIBIM_GAMEASSETLOADINGTASK_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class GameAssetLoadingTask
        {
            public:
                GameAssetLoadingTask();
                virtual ~GameAssetLoadingTask();

                virtual void Execute() = 0;
        };
    }

#endif