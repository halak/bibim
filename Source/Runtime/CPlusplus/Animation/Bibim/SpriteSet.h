#pragma once
#ifndef __BIBIM_SPRITESET_H__
#define __BIBIM_SPRITESET_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>
#   include <Bibim/Sprite.h>
#   include <Bibim/String.h>
#   include <vector>

    namespace Bibim
    {
        class SpriteSet : public GameAsset
        {
            BBSerializableAssetClass(SpriteSet, GameAsset, 'S', 'P', 'R', 'S');
            public:
                SpriteSet();
                virtual ~SpriteSet();

                Sprite* Find(const String& name) const;

            private:
                typedef std::pair<String, SpritePtr> Item;
                typedef std::vector<Item> ItemCollection;

                SpriteSet(ItemCollection& items);

            private:
                ItemCollection items;
        };
    }

#endif