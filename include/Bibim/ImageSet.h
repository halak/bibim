#pragma once
#ifndef __BIBIM_IMAGESET_H__
#define __BIBIM_IMAGESET_H__

#include <Bibim/FWD.h>
#include <Bibim/GameAsset.h>
#include <Bibim/Image.h>
#include <Bibim/String.h>
#include <vector>

namespace Bibim
{
    class ImageSet : public GameAsset
    {
        BBSerializableAssetClass(ImageSet, GameAsset, 'I', 'M', 'G', 'S');
        public:
            ImageSet();
            virtual ~ImageSet();

            Image* Find(const String& name) const;

        private:
            typedef std::pair<String, ImagePtr> Item;
            typedef std::vector<Item> ItemCollection;

            ImageSet(ItemCollection& items);

        private:
            ItemCollection items;
    };
}

#endif