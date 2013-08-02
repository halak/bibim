#include <Bibim/Config.h>
#include <Bibim/GameAssetFactory.h>
#include <Bibim/Assert.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/GameAsset.h>
#include <algorithm>
#include <vector>

namespace Bibim
{
    struct GameAssetFactory::Entry
    {
        int ID;
        GameAssetFactory::CreateFunction Function;

        Entry(int id, GameAssetFactory::CreateFunction function)
            : ID(id),
              Function(function)
        {
        }

        static std::vector<Entry> Items;
    };

    std::vector<GameAssetFactory::Entry> GameAssetFactory::Entry::Items;

    GameAssetFactory::Entry* GameAssetFactory::FindEntry(int id)
    {
        BBAssertDebug(Entry::Items.empty() == false);

        int lower = 0;
        int upper = static_cast<int>(Entry::Items.size());

        while (upper - lower > 0)
        {
            const int index = lower + static_cast<int>((upper - lower) / 2);

            if (id < Entry::Items[index].ID)
                upper = index;
            else if (id > Entry::Items[index].ID)
                lower = index;
            else
                return &Entry::Items[index];
        }

        return nullptr;
    }

    void GameAssetFactory::AddEntry(int id, CreateFunction function)
    {
        Entry::Items.push_back(Entry(id, function));
    }

    void GameAssetFactory::SortEntries()
    {
        struct Compare
        {
            static bool Do(const Entry& a, const Entry& b)
            {
                return a.ID < b.ID;
            }
        };

        std::sort(Entry::Items.begin(), Entry::Items.end(), Compare::Do);
    }

    GameAsset* GameAssetFactory::Create(StreamReader& reader, GameAsset* existingInstance)
    {
        const int id = reader.ReadInt();
        if (Entry* entry = FindEntry(id))
        {
            BBAssert(existingInstance == nullptr ||
                     existingInstance->GetClassID() == id);
            return (*entry->Function)(reader, existingInstance);
        }
        else
            return nullptr;
    }
}