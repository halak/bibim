namespace Bibim
{
    template <typename T, char a, char b, char c, char d>
    EvalVariableTemplate<T, a, b, c, d>* EvalVariableTemplate<T, a, b, c, d>::Clone() const
    {
        CloningContext context;
        return Clone(context);
    }

    template <typename T, char a, char b, char c, char d>
    EvalVariableTemplate<T, a, b, c, d>* EvalVariableTemplate<T, a, b, c, d>::Clone(CloningContext& context) const
    {
        This* clone = new This();
        context.Store(this, clone);
        clone->OnCopy(this, context);
        return clone;
    }

    template <typename T, char a, char b, char c, char d>
    T EvalVariableTemplate<T, a, b, c, d>::Evaluate(EvalContext& context)
    {
        return context.GetValue<T>(name);
    }

    template <typename T, char a, char b, char c, char d>
    void EvalVariableTemplate<T, a, b, c, d>::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        name = reader.ReadString();
    }

    template <typename T, char a, char b, char c, char d>
    void EvalVariableTemplate<T, a, b, c, d>::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        name = o->name;
    }
}