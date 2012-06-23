#include <Bibim/PCH.h>
#include <Bibim/ImageSet.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/GameAssetStorage.h>

namespace Bibim
{
    ImageSet::ImageSet()
    {
        // for cloning and deserialization
    }

    ImageSet::ImageSet(ItemCollection& items)
    {
        this->items.swap(items);
    }

    ImageSet::~ImageSet()
    {
    }

    Image* ImageSet::Find(const String& name) const
    {
        for (ItemCollection::const_iterator it = items.begin(); it != items.end(); it++)
        {
            if ((*it).first == name)
                return (*it).second;
        }

        return nullptr;
    }

    GameAsset* ImageSet::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        const int count = static_cast<int>(reader.ReadShortInt());
        ItemCollection items;
        items.reserve(count);
        for (int i = 0; i < count; i++)
        {
            String name = reader.ReadString();
            ImagePtr image = static_cast<Image*>(Image::Create(reader, nullptr));
            items.push_back(Item(name, image));
        }

        return new ImageSet(items);
    }
}