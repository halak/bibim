#include <Bibim/Config.h>
#include <Bibim/GameComponentFactory.h>
#include <Bibim/Assert.h>
#include <Bibim/ComponentStreamReader.h>
#include <algorithm>
#include <vector>

namespace Bibim
{
    struct Entry
    {
        int ID;
        GameComponentFactory::CreateFunction Function;

        Entry(int id, GameComponentFactory::CreateFunction function)
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

    void GameComponentFactory::AddEntry(int id, CreateFunction function)
    {
        Entries.push_back(Entry(id, function));
    }

    void GameComponentFactory::SortEntries()
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

    GameComponent* GameComponentFactory::Create(int id)
    {
        if (Entry* entry = FindEntry(id))
            return (*entry->Function)();
        else
            return nullptr;
    }
}