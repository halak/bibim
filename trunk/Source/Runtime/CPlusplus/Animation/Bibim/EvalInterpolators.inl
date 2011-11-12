namespace Bibim
{
    template <typename T, template <typename T> class TOperator, char a, char b, char c, char d>
    EvalInterpolatorTemplate<T, TOperator, a, b, c, d>* EvalInterpolatorTemplate<T, TOperator, a, b, c, d>::Clone() const
    {
        CloningContext context;
        return Clone(context);
    }

    template <typename T, template <typename T> class TOperator, char a, char b, char c, char d>
    EvalInterpolatorTemplate<T, TOperator, a, b, c, d>* EvalInterpolatorTemplate<T, TOperator, a, b, c, d>::Clone(CloningContext& context) const
    {
        This* clone = new This();
        context.Store(this, clone);
        clone->OnCopy(this, context);
        return clone;
    }

    template <typename T, template <typename T> class TOperator, char a, char b, char c, char d>
    void EvalInterpolatorTemplate<T, TOperator, a, b, c, d>::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        value1 = static_cast<EvalValue*>(reader.ReadComponent());
        value2 = static_cast<EvalValue*>(reader.ReadComponent());
        weight = static_cast<EvalFloat*>(reader.ReadComponent());
        easingCurve = static_cast<EasingCurve*>(reader.ReadComponent());
    }

    template <typename T, template <typename T> class TOperator, char a, char b, char c, char d>
    void EvalInterpolatorTemplate<T, TOperator, a, b, c, d>::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        value1 = context.Clone(o->value1);
        value2 = context.Clone(o->value2);
        weight = context.Clone(o->weight);
        easingCurve = context.Clone(o->easingCurve);
    }
}