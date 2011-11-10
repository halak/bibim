using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    public abstract class EvalUnaryOperatorTemplate<T, TOperand> : Eval<T>
    {
        #region Properties
        public Eval<TOperand> Operand
        {
            get;
            set;
        }
        #endregion

        public sealed override void Reset()
        {
            if (Operand != null)
                Operand.Reset();
        }

        public sealed override T Evaluate(EvalContext context)
        {
            if (Operand != null)
                return Calculate(Operand.Evaluate(context));
            else
                return default(T);
        }

        protected abstract T Calculate(TOperand value);
    }
}
