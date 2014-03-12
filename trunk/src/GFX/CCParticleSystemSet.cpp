#include <Bibim/Config.h>
#include <Bibim/CCParticleSystemSet.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/GameAssetStorage.h>

namespace Bibim
{
    CCParticleSystemSet::CCParticleSystemSet()
    {
        // for cloning and deserialization
    }

    CCParticleSystemSet::CCParticleSystemSet(ItemCollection& items)
    {
        this->items.swap(items);
    }

    CCParticleSystemSet::~CCParticleSystemSet()
    {
    }

    CCParticleSystem* CCParticleSystemSet::Find(const String& name) const
    {
        for (ItemCollection::const_iterator it = items.begin(); it != items.end(); ++it)
        {
            if ((*it).first == name)
                return (*it).second;
        }

        return nullptr;
    }

    GameAsset* CCParticleSystemSet::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        const int count = static_cast<int>(reader.ReadShortInt());
        ItemCollection items;
        items.reserve(count);
        for (int i = 0; i < count; i++)
        {
            String name = reader.ReadString();
            CCParticleSystem* value = static_cast<CCParticleSystem*>(CCParticleSystem::Create(reader, nullptr));
            items.push_back(Item(name, value));
        }

        return new CCParticleSystemSet(items);
    }
}