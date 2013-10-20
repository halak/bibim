#include <Bibim/Config.h>
#include <Bibim/SparkSet.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/GameAssetStorage.h>

namespace Bibim
{
    SparkSet::SparkSet()
    {
        // for cloning and deserialization
    }

    SparkSet::SparkSet(ItemCollection& items, ImageSet* images)
    {
        this->items.swap(items);
        this->images = images;
    }

    SparkSet::~SparkSet()
    {
    }

    Spark* SparkSet::Find(const String& name) const
    {
        for (ItemCollection::const_iterator it = items.begin(); it != items.end(); it++)
        {
            if ((*it).first == name)
                return (*it).second;
        }

        return nullptr;
    }

    GameAsset* SparkSet::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        ImageSet* images = static_cast<ImageSet*>(ImageSet::Create(reader, nullptr));

        const int count = static_cast<int>(reader.ReadShortInt());
        ItemCollection items;
        items.reserve(count);
        for (int i = 0; i < count; i++)
        {
            String name = reader.ReadString();
            SparkPtr spark = static_cast<Spark*>(Spark::Create(reader, nullptr));
            spark->SetImages(images);
            items.push_back(Item(name, spark));
        }

        return new SparkSet(items, images);
    }
}