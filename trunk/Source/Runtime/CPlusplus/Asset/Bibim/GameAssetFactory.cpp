#include <Bibim/PCH.h>
#include <Bibim/GameAssetFactory.h>
#include <Bibim/Assert.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/GameAsset.h>
#include <algorithm>
#include <vector>

namespace Bibim
{
    struct Entry
    {
        int ID;
        GameAssetFactory::CreateFunction Function;

        Entry(int id, GameAssetFactory::CreateFunction function)
            : ID(id),
              Function(function)
        {
        }
    };

    static std::vector<Entry> Entries;

    static Entry* FindEntry(int id)
    {
        BBAssertDebug(Entries.empty() == false);

        int lower = 0;
        int upper = static_cast<int>(Entries.size());

        while (upper - lower > 0)
        {
            const int index = lower + static_cast<int>((upper - lower) / 2);

            if (id < Entries[index].ID)
                upper = index;
            else if (id > Entries[index].ID)
                lower = index;
            else
                return &Entries[index];
        }

        return nullptr;
    }

    void GameAssetFactory::AddEntry(int id, CreateFunction function)
    {
        Entries.push_back(Entry(id, function));
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

        std::sort(Entries.begin(), Entries.end(), Compare::Do);
    }

    GameAsset* GameAssetFactory::Create(StreamReader& reader, GameAsset* existingInstance)
    {
        const int id = reader.ReadInt();
        if (Entry* entry = FindEntry(id))
            return (*entry->Function)(reader, existingInstance);
        else
            return nullptr;
    }
}