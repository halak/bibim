#include <Bibim/PCH.h>
#include <Bibim/EvalBoard.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    EvalBoard::EvalBoard()
    {
    }

    EvalBoard::EvalBoard(std::vector<Item>& items)
    {
        this->items.swap(items);
    }

    EvalBoard::~EvalBoard()
    {
    }

    EvalBase* EvalBoard::Find(const String& name) const
    {
        for (ItemCollection::const_iterator it = items.begin(); it != items.end(); it++)
        {
            if ((*it).Name == name)
                return (*it).Root;
        }

        return nullptr;
    }

    GameAsset* EvalBoard::Create(AssetStreamReader& reader, GameAsset* /*existingInstance*/)
    {
        const int count = static_cast<int>(reader.ReadShortInt());
        std::vector<Item> items;
        items.reserve(count);
        Item newItem;
        for (int i = 0; i < count; i++)
        {
            newItem.Name = reader.ReadString();
            ComponentStreamReader evalReader(reader.GetSource(), reader.GetModules());
            newItem.Root = static_cast<EvalBase*>(evalReader.ReadComponent());
            items.push_back(newItem);
        }

        return new EvalBoard(items);
    }
}