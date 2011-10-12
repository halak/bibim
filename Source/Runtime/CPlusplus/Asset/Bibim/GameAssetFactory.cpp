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
        uint32 ID;
        GameAssetFactory::CreateFunction Function;

        Entry(uint32 id, GameAssetFactory::CreateFunction function)
            : ID(id),
              Function(function)
        {
        }
    };

    static std::vector<Entry> Entries;

    static Entry* FindEntry(uint32 id)
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

    void GameAssetFactory::AddEntry(uint32 id, CreateFunction function)
    {
        Entries.push_back(Entry(id, function));
    }

    void GameAssetFactory::SortEntries()
    {
        struct Compare
        {
            bool operator () (const Entry& a, const Entry& b)
            {
                return a.ID < b.ID;
            }
        };

        std::sort(Entries.begin(), Entries.end(), Compare());
    }

    GameAsset* GameAssetFactory::Create(StreamReader& reader, GameAsset* existingInstance)
    {
        const uint32 id = reader.ReadUInt32();

        if (Entry* entry = FindEntry(id))
            return (*entry->Function)(reader, existingInstance);
        else
            return nullptr;
    }
}