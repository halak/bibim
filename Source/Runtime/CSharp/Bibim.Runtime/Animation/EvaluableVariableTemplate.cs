using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    public abstract class EvaluableVariableTemplate<T> : Evaluable<T>
    {
        #region Fields
        private string name;
        #endregion

        #region Properties
        public string Name
        {
            get { return name; }
            set
            {
                name = value ?? string.Empty;
            }
        }
        #endregion

        #region Constructors
        protected EvaluableVariableTemplate()
            : this(string.Empty)
        {
        }

        protected EvaluableVariableTemplate(string value)
        {
            Name = value;
        }
        #endregion

        public override T Evaluate(EvaluationContext context)
        {
            return default(T);
        }
    }
}
