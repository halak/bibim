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
}