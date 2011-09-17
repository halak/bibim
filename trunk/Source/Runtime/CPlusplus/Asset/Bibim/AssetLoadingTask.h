#pragma once
#ifndef __BIBIM_GAMEASSETLOADINGTASK_H__
#define __BIBIM_GAMEASSETLOADINGTASK_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class AssetLoadingTask
        {
            public:
                AssetLoadingTask();
                virtual ~AssetLoadingTask();

                virtual void Execute() = 0;
        };
    }

#endif