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

        public override T Evaluate(EvalContext context)
        {
            return Value;
        }

        #region IXmlSerializable
        public override void ReadXml(System.Xml.XmlReader reader)
        {
            throw new NotImplementedException();
        }

        public override void WriteXml(System.Xml.XmlWriter writer)
        {
            throw new NotImplementedException();
        }
        #endregion
    }
}
