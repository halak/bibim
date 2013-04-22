#include <Bibim/Config.h>
#include <Bibim/SpriteSet.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/GameAssetStorage.h>

namespace Bibim
{
    SpriteSet::SpriteSet()
    {
        // for cloning and deserialization
    }

    SpriteSet::SpriteSet(ItemCollection& items)
    {
        this->items.swap(items);
    }

    SpriteSet::~SpriteSet()
    {
    }

    Sprite* SpriteSet::Find(const String& name) const
    {
        for (ItemCollection::const_iterator it = items.begin(); it != items.end(); it++)
        {
            if ((*it).first == name)
                return (*it).second;
        }

        return nullptr;
    }

    GameAsset* SpriteSet::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        const int count = static_cast<int>(reader.ReadShortInt());
        ItemCollection items;
        items.reserve(count);
        for (int i = 0; i < count; i++)
        {
            String name = reader.ReadString();
            SpritePtr image = static_cast<Sprite*>(Sprite::Create(reader, nullptr));
            items.push_back(Item(name, image));
        }

        return new SpriteSet(items);
    }
}