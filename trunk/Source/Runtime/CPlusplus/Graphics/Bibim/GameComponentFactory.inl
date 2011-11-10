namespace Bibim
{
    template <typename T> void GameComponentFactory::AddEntry()
    {
        struct New
        {
            static GameComponent* Do()
            {
                return new T();
            }
        };

        AddEntry(T::ClassID, &New::Do);
    }

    template <typename T> void GameComponentFactory::AddSingletonEntry()
    {
        struct Get
        {
            static GameComponent* Do()
            {
                return T::Instance;
            }
        };

        AddEntry(T::ClassID, &Get::Do);
    }
}