using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Animation
{
    public abstract class EvalConstantTemplate<T> : Eval<T>
    {
        #region Properties
        public T Value
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        protected EvalConstantTemplate()
        {
            Value = default(T);
        }

        protected EvalConstantTemplate(T value)
        {
            Value = value;
        }
        #endregion

        public sealed override void Start() { }
        public sealed override void Stop() { }
        public sealed override void Reset() { }

        public sealed override T Evaluate(EvalContext context)
        {
            return Value;
        }
    }
}
