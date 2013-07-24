namespace Bibim
{
    template <typename T, char a, char b, char c, char d>
    EvalSelectorTemplate<T, a, b, c, d>* EvalSelectorTemplate<T, a, b, c, d>::Clone() const
    {
        CloningContext context;
        return Clone(context);
    }

    template <typename T, char a, char b, char c, char d>
    EvalSelectorTemplate<T, a, b, c, d>* EvalSelectorTemplate<T, a, b, c, d>::Clone(CloningContext& context) const
    {
        This* clone = new This();
        context.Store(this, clone);
        clone->OnCopy(this, context);
        return clone;
    }

    template <typename T, char a, char b, char c, char d>
    void EvalSelectorTemplate<T, a, b, c, d>::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        condition = static_cast<EvalFloat*>(reader.ReadComponent());
        const int count = static_cast<int>(reader.ReadShortInt());
        cases.resize(count);
        for (int i = 0; i < count; i++)
        {
            cases[i].Min = reader.ReadFloat();
            cases[i].Max = reader.ReadFloat();
            cases[i].Item = static_cast<EvalTemplate<T>*>(reader.ReadComponent());
        }
        defaultCase = static_cast<EvalTemplate<T>*>(reader.ReadComponent());
    }

    template <typename T, char a, char b, char c, char d>
    void EvalSelectorTemplate<T, a, b, c, d>::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        condition = context.Clone(o->condition);
        cases.reserve(o->cases.size());
        for (typename CaseCollection::const_iterator it = o->cases.begin(); it != o->cases.end(); it++)
        {
            const Case& item = (*it);
            cases.push_back(Case(item.Min, item.Max, context.Clone(item.Item)));
        }
        defaultCase = context.Clone(o->defaultCase);
    }
}