namespace Bibim
{
    template <typename T> void GameModuleFactory::AddEntry()
    {
        struct Create
        {
            static GameModule* Do()
            {
                return new T();
            }
        };

        AddEntry(T::ClassID, &Create::Do);
    }
}