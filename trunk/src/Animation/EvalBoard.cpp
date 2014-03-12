#include <Bibim/Config.h>
#include <Bibim/EvalBoard.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    EvalBoard::EvalBoard()
        : duration(0.0f)
    {
    }

    EvalBoard::EvalBoard(float duration, std::vector<Item>& items)
        : duration(duration)
    {
        this->items.swap(items);
    }

    EvalBoard::~EvalBoard()
    {
    }

    EvalBase* EvalBoard::Find(const String& name) const
    {
        for (ItemCollection::const_iterator it = items.begin(); it != items.end(); ++it)
        {
            if ((*it).Name == name)
                return (*it).Root;
        }

        return nullptr;
    }

    GameAsset* EvalBoard::Create(AssetStreamReader& reader, GameAsset* /*existingInstance*/)
    {
        const float duration = reader.ReadFloat();
        const int count = static_cast<int>(reader.ReadShortInt());
        std::vector<Item> items;
        items.reserve(count);
        Item newItem;
        ComponentStreamReader evalReader(reader.GetSource(), reader.GetModules());
        for (int i = 0; i < count; i++)
        {
            newItem.Name = reader.ReadString();
            newItem.Root = static_cast<EvalBase*>(evalReader.ReadComponent());
            items.push_back(newItem);
        }

        return new EvalBoard(duration, items);
    }
}