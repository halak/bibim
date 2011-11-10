using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

namespace Bibim.Animation
{
    public abstract class EvalBase : GameComponent
    {
        #region Properties
        [XmlIgnore]
        protected abstract Type EvaluableType
        {
            get;
        }
        #endregion

        public abstract void Start();
        public abstract void Stop();
        public abstract void Reset();
    }

    public abstract class Eval<T> : EvalBase
    {
        #region Properties
        protected override Type EvaluableType
        {
            get { return typeof(T); }
        }
        #endregion

        public abstract T Evaluate(EvalContext context);
    }
}
