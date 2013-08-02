using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    public abstract class EvalBinaryOperatorTemplate<T, TLeft, TRight> : Eval<T>
    {
        #region Properties
        public Eval<TLeft> Left
        {
            get;
            set;
        }

        public Eval<TRight> Right
        {
            get;
            set;
        }
        #endregion

        public sealed override void Start()
        {
            if (Left != null)
                Left.Start();
            if (Right != null)
                Right.Start();
        }

        public sealed override void Stop()
        {
            if (Left != null)
                Left.Stop();
            if (Right != null)
                Right.Stop();
        }

        public sealed override void Reset()
        {
            if (Left != null)
                Left.Reset();
            if (Right != null)
                Right.Reset();
        }

        public sealed override T Evaluate(EvalContext context)
        {
            if (Left != null && Right != null)
                return Calculate(Left.Evaluate(context), Right.Evaluate(context));
            else
                return default(T);
        }

        protected abstract T Calculate(TLeft left, TRight right);
    }
}
