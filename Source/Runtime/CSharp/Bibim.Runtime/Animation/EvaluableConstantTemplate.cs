using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    public abstract class EvaluableConstantTemplate<T> : Evaluable<T>
    {
        #region Properties
        public T Value
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        protected EvaluableConstantTemplate()
        {
            Value = default(T);
        }

        protected EvaluableConstantTemplate(T value)
        {
            Value = value;
        }
        #endregion

        public override T Evaluate(EvaluationContext context)
        {
            return Value;
        }
    }
}
