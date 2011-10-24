namespace Bibim
{
    template <typename T, char a, char b, char c, char d>
    EvaluableConstantTemplate<T, a, b, c, d>::EvaluableConstantTemplate()
        : value()
    {
    }

    template <typename T, char a, char b, char c, char d>
    EvaluableConstantTemplate<T, a, b, c, d>::EvaluableConstantTemplate(T value)
        : value(value)
    {
    }

    template <typename T, char a, char b, char c, char d>
    EvaluableConstantTemplate<T, a, b, c, d>::~EvaluableConstantTemplate()
    {
    }

    template <typename T, char a, char b, char c, char d>
    EvaluableConstantTemplate<T, a, b, c, d>* EvaluableConstantTemplate<T, a, b, c, d>::Clone(CloningContext& /*context*/) const
    {
        This* clone = new This();
        return clone;
    }

    template <typename T, char a, char b, char c, char d>
    T EvaluableConstantTemplate<T, a, b, c, d>::Evaluate(EvaluationContext& /*context*/)
    {
        return value;
    }

    template <typename T, char a, char b, char c, char d>
    T EvaluableConstantTemplate<T, a, b, c, d>::GetValue() const
    {
        return value;
    }

    template <typename T, char a, char b, char c, char d>
    void EvaluableConstantTemplate<T, a, b, c, d>::SetValue(T value)
    {
        this->value = value;
    }

    template <typename T, char a, char b, char c, char d>
    void EvaluableConstantTemplate<T, a, b, c, d>::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    template <typename T, char a, char b, char c, char d>
    void EvaluableConstantTemplate<T, a, b, c, d>::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    GameAsset* EvaluableGameAssetConstant::GetValue() const
    {
        return value;
    }

    void EvaluableGameAssetConstant::SetValue(GameAsset* value)
    {
        this->value = value;
    }
}