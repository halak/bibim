using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

namespace Bibim.Animation
{
    public abstract class Eval<T> : GameComponent, IXmlSerializable
    {
        public abstract T Evaluate(EvalContext context);

        #region IXmlSerializable
        public System.Xml.Schema.XmlSchema GetSchema()
        {
            return null;
        }

        public abstract void ReadXml(XmlReader reader);
        public abstract void WriteXml(XmlWriter writer);
        #endregion
    }
}
