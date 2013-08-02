#include <Bibim/Config.h>
#include <Bibim/GameComponentFactory.h>
#include <Bibim/Assert.h>
#include <Bibim/ComponentStreamReader.h>
#include <algorithm>
#include <vector>

namespace Bibim
{
    struct GameComponentFactory::Entry
    {
        int ID;
        GameComponentFactory::CreateFunction Function;

        Entry(int id, GameComponentFactory::CreateFunction function)
            : ID(id),
              Function(function)
        {
        }

        static std::vector<Entry> Items;
    };

    std::vector<GameComponentFactory::Entry> GameComponentFactory::Entry::Items;

    GameComponentFactory::Entry* GameComponentFactory::FindEntry(int id)
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

    void GameComponentFactory::AddEntry(int id, CreateFunction function)
    {
        Entry::Items.push_back(Entry(id, function));
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

        std::sort(Entry::Items.begin(), Entry::Items.end(), Compare::Do);
    }

    GameComponent* GameComponentFactory::Create(int id)
    {
        if (Entry* entry = FindEntry(id))
            return (*entry->Function)();
        else
            return nullptr;
    }
}