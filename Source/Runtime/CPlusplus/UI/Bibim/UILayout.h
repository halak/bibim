#pragma once
#ifndef __BIBIM_UILAYOUT_H__
#define __BIBIM_UILAYOUT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>

    namespace Bibim
    {
        class UILayout : public GameAsset
        {
            BBCreatableObjectClass(UILayout, GameAsset, GameAsset, 'U', 'I', 'L', 'T');
            public:
                UILayout();
                virtual ~UILayout();

            private:
        };
    }

#endif