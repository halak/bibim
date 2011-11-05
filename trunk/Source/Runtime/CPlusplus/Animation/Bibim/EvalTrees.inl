namespace Bibim
{
    template <typename T, char a, char b, char c, char d>
    EvalTreeTemplate<T, a, b, c, d>::EvalTreeTemplate()
    {
    }

    template <typename T, char a, char b, char c, char d>
    EvalTreeTemplate<T, a, b, c, d>::EvalTreeTemplate(Eval* root)
        : root(root)
    {
    }

    template <typename T, char a, char b, char c, char d>
    EvalTreeTemplate<T, a, b, c, d>::~EvalTreeTemplate()
    {
    }

    template <typename T, char a, char b, char c, char d>
    typename EvalTreeTemplate<T, a, b, c, d>::Eval* EvalTreeTemplate<T, a, b, c, d>::GetRoot() const
    {
        return root;
    }

    template <typename T, char a, char b, char c, char d>
    void EvalTreeTemplate<T, a, b, c, d>::SetRoot(Eval* value)
    {
        root = value;
    }

    template <typename T, char a, char b, char c, char d>
    GameAsset* EvalTreeTemplate<T, a, b, c, d>::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        ComponentStreamReader evalReader(reader.GetSource(), reader.GetModules());
        return new This(static_cast<Eval*>(evalReader.ReadComponent()));
    }
}