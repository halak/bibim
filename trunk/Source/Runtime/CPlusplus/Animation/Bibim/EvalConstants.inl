namespace Bibim
{
    template <typename T, char a, char b, char c, char d>
    EvalConstantTemplate<T, a, b, c, d>* EvalConstantTemplate<T, a, b, c, d>::Clone() const
    {
        CloningContext context;
        return Clone(context);
    }

    template <typename T, char a, char b, char c, char d>
    EvalConstantTemplate<T, a, b, c, d>* EvalConstantTemplate<T, a, b, c, d>::Clone(CloningContext& context) const
    {
        This* clone = new This();
        context.Store(this, clone);
        clone->OnCopy(this, context);
        return clone;
    }

    template <typename T, char a, char b, char c, char d>
    void EvalConstantTemplate<T, a, b, c, d>::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        reader.Read(value);
    }

    template <typename T, char a, char b, char c, char d>
    void EvalConstantTemplate<T, a, b, c, d>::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        value = o->value;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    GameAsset* EvalGameAssetConstant::GetValue() const
    {
        return value;
    }

    void EvalGameAssetConstant::SetValue(GameAsset* value)
    {
        this->value = value;
    }
}