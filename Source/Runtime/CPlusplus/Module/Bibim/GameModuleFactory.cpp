#include <Bibim/PCH.h>
#include <Bibim/GameModuleFactory.h>
#include <Bibim/Assert.h>
#include <Bibim/GameModule.h>
#include <algorithm>
#include <vector>

namespace Bibim
{
    struct Entry
    {
        uint32 ID;
        GameModuleFactory::CreateFunction Function;

        Entry(uint32 id, GameModuleFactory::CreateFunction function)
            : ID(id),
              Function(function)
        {
        }
    };

    static std::vector<Entry> Entries;

    void GameModuleFactory::AddEntry(uint32 id, CreateFunction function)
    {
        Entries.push_back(Entry(id, function));
    }

    void GameModuleFactory::SortEntries()
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

    GameModule* GameModuleFactory::Create(uint32 id)
    {
        BBAssertDebug(Entries.empty() == false);

        int lower = 0;
        int upper = static_cast<int>(Entries.size());

        while (upper - lower > 0)
        {
            const int index = lower + static_cast<int>((upper - lower) / 2);

            if (id < Entries[index].ID)
                upper = index + 1;
            else if (id > Entries[index].ID)
                lower = index;
            else
                return (*Entries[index].Function)();
        }

        return nullptr;
    }
}