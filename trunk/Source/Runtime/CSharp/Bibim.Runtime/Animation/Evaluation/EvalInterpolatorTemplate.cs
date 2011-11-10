using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    public abstract class EvalInterpolatorTemplate<T> : Eval<T>
    {
        #region Properties
        public Eval<T> Value1
        {
            get;
            set;
        }

        public Eval<T> Value2
        {
            get;
            set;
        }

        public Eval<float> Weight
        {
            get;
            set;
        }
        #endregion

        public sealed override void Reset()
        {
            if (Value1 != null)
                Value1.Reset();
            if (Value2 != null)
                Value2.Reset();
            if (Weight != null)
                Weight.Reset();
        }

        public sealed override T Evaluate(EvalContext context)
        {
            if (Value1 != null && Value2 != null && Weight != null)
                return Interpolate(Value1.Evaluate(context), Value2.Evaluate(context), Weight.Evaluate(context));
            else
                return default(T);
        }

        public abstract T Interpolate(T a, T b, float t);
    }
}
