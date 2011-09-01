namespace Bibim
{
    template <typename T> void GameComponentFactory::AddEntry()
    {
        struct Create
        {
            static GameComponent* Do()
            {
                return new T();
            }
        };

        AddEntry(T::ClassID, &Create::Do);
    }
}