namespace Bibim
{
    template <typename T>
    void EvalTemplate<T>::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    template <typename T>
    void EvalTemplate<T>::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}