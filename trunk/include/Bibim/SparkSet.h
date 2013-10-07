#pragma once
#ifndef __BIBIM_SPARKSET_H__
#define __BIBIM_SPARKSET_H__

#include <Bibim/FWD.h>
#include <Bibim/GameAsset.h>
#include <Bibim/ImageSet.h>
#include <Bibim/Spark.h>
#include <Bibim/String.h>
#include <vector>

namespace Bibim
{
    class SparkSet : public GameAsset
    {
        BBSerializableAssetClass(SparkSet, GameAsset, 'S', 'P', 'K', 'S');
        public:
            SparkSet();
            virtual ~SparkSet();

            Spark* Find(const String& name) const;

        private:
            typedef std::pair<String, SparkPtr> Item;
            typedef std::vector<Item> ItemCollection;

            SparkSet(ItemCollection& items, ImageSet* images);

        private:
            ItemCollection items;
            ImageSetPtr images;
    };
}

#endif