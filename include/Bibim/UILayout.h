#pragma once
#ifndef __BIBIM_UILAYOUT_H__
#define __BIBIM_UILAYOUT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>

    namespace Bibim
    {
        class UILayout : public GameAsset
        {
            BBSerializableAssetClass(UILayout, GameAsset, 'U', 'I', 'L', 'T');
            public:
                UILayout();
                UILayout(UIWindow* root);
                virtual ~UILayout();

                inline UIWindow* GetRoot() const;

            private:
                UIWindowPtr root;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        UIWindow* UILayout::GetRoot() const
        {
            return root;
        }
    }

#endif