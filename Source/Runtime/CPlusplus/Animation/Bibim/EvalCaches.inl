namespace Bibim
{
    template <typename T, char a, char b, char c, char d>
    EvalCacheTemplate<T, a, b, c, d>* EvalCacheTemplate<T, a, b, c, d>::Clone() const
    {
        CloningContext context;
        return Clone(context);
    }

    template <typename T, char a, char b, char c, char d>
    EvalCacheTemplate<T, a, b, c, d>* EvalCacheTemplate<T, a, b, c, d>::Clone(CloningContext& context) const
    {
        This* clone = new This();
        context.Store(this, clone);
        clone->OnCopy(this, context);
        return clone;
    }

    template <typename T, char a, char b, char c, char d>
    void EvalCacheTemplate<T, a, b, c, d>::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        source = static_cast<EvalTemplate<T>*>(reader.ReadComponent());
        updateMode = static_cast<EvalCacheUpdateMode>(reader.ReadByte());
        valueChanged = true;
    }

    template <typename T, char a, char b, char c, char d>
    void EvalCacheTemplate<T, a, b, c, d>::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        value = o->value;
        source = context.Clone(o->source);
        updateMode = o->updateMode;
        valueChanged = o->valueChanged;
    }
}