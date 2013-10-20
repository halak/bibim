#pragma once
#ifndef __BIBIM_CCPARTICLESYSTEMSET_H__
#define __BIBIM_CCPARTICLESYSTEMSET_H__

#include <Bibim/FWD.h>
#include <Bibim/GameAsset.h>
#include <Bibim/CCParticleSystem.h>
#include <Bibim/String.h>
#include <vector>

namespace Bibim
{
    class CCParticleSystemSet : public GameAsset
    {
        BBSerializableAssetClass(CCParticleSystemSet, GameAsset, 'P', 'S', 'S', 'T');
        public:
            CCParticleSystemSet();
            virtual ~CCParticleSystemSet();

            CCParticleSystem* Find(const String& name) const;

        private:
            typedef std::pair<String, CCParticleSystemPtr> Item;
            typedef std::vector<Item> ItemCollection;

            CCParticleSystemSet(ItemCollection& items);

        private:
            ItemCollection items;
    };
}

#endif