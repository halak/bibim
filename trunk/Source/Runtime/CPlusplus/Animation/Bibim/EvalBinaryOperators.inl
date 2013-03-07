#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    template <typename T, typename TLeft, typename TRight, template <typename T, typename TLeft, typename TRight> class TOperator, char a, char b, char c, char d>
    EvalBinaryOperatorTemplate<T, TLeft, TRight, TOperator, a, b, c, d>* EvalBinaryOperatorTemplate<T, TLeft, TRight, TOperator, a, b, c, d>::Clone() const
    {
        CloningContext context;
        return Clone(context);
    }

    template <typename T, typename TLeft, typename TRight, template <typename T, typename TLeft, typename TRight> class TOperator, char a, char b, char c, char d>
    EvalBinaryOperatorTemplate<T, TLeft, TRight, TOperator, a, b, c, d>* EvalBinaryOperatorTemplate<T, TLeft, TRight, TOperator, a, b, c, d>::Clone(CloningContext& context) const
    {
        This* clone = new This();
        context.Store(this, clone);
        clone->OnCopy(this, context);
        return clone;
    }

    template <typename T, typename TLeft, typename TRight, template <typename T, typename TLeft, typename TRight> class TOperator, char a, char b, char c, char d>
    void EvalBinaryOperatorTemplate<T, TLeft, TRight, TOperator, a, b, c, d>::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        left = static_cast<EvalLeft*>(reader.ReadComponent());
        right = static_cast<EvalRight*>(reader.ReadComponent());
    }

    template <typename T, typename TLeft, typename TRight, template <typename T, typename TLeft, typename TRight> class TOperator, char a, char b, char c, char d>
    void EvalBinaryOperatorTemplate<T, TLeft, TRight, TOperator, a, b, c, d>::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        left = context.Clone(o->left);
        right = context.Clone(o->right);
    }
}