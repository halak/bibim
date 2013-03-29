#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    template <typename T, typename TOperand, template <typename U, typename UOperand> class TOperator, char a, char b, char c, char d>
    EvalUnaryOperatorTemplate<T, TOperand, TOperator, a, b, c, d>* EvalUnaryOperatorTemplate<T, TOperand, TOperator, a, b, c, d>::Clone() const
    {
        CloningContext context;
        return Clone(context);
    }

    template <typename T, typename TOperand, template <typename U, typename UOperand> class TOperator, char a, char b, char c, char d>
    EvalUnaryOperatorTemplate<T, TOperand, TOperator, a, b, c, d>* EvalUnaryOperatorTemplate<T, TOperand, TOperator, a, b, c, d>::Clone(CloningContext& context) const
    {
        This* clone = new This();
        context.Store(this, clone);
        clone->OnCopy(this, context);
        return clone;
    }

    template <typename T, typename TOperand, template <typename U, typename UOperand> class TOperator, char a, char b, char c, char d>
    void EvalUnaryOperatorTemplate<T, TOperand, TOperator, a, b, c, d>::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        operand = static_cast<Eval*>(reader.ReadComponent());
    }

    template <typename T, typename TOperand, template <typename U, typename UOperand> class TOperator, char a, char b, char c, char d>
    void EvalUnaryOperatorTemplate<T, TOperand, TOperator, a, b, c, d>::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        operand = context.Clone(o->operand);
    }
}