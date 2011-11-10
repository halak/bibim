using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Xml;
using System.Xml.Schema;
using System.Xml.Serialization;
using Bibim.Animation;
using Bibim.Reflection;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class ReadGameAsset : CookingNode<GameAsset>, IXmlSerializable
    {
        #region Fields
        private static DataContractSerializer serializer;
        #endregion

        #region Properties
        [XmlIgnore]
        public GameAsset Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public ReadGameAsset()
        {
        }

        public ReadGameAsset(GameAsset input)
        {
            Input = input;
        }
        #endregion

        #region Properties
        private static DataContractSerializer Serializer
        {
            get
            {
                if (serializer == null)
                {
                    ICollection<Type> classes1 = AssemblyUtility.FindClasses(typeof(GameAsset), true, true);
                    ICollection<Type> classes2 = AssemblyUtility.FindClasses(typeof(EvalBase), true, true);
                    ICollection<Type> classes3 = AssemblyUtility.FindClasses(typeof(EasingCurve), true, true);

                    Type[] types = new Type[classes1.Count + classes2.Count + classes3.Count];
                    classes1.CopyTo(types, 0);
                    classes2.CopyTo(types, classes1.Count);
                    classes3.CopyTo(types, classes1.Count + classes2.Count);

                    serializer = new DataContractSerializer(typeof(GameAsset), types, 128, false, true, null);
                }

                return serializer;
            }
        }
        #endregion

        public override GameAsset Cook(CookingContext context)
        {
            return Input;
        }

        #region IXmlSerializable
        public XmlSchema GetSchema()
        {
            return null;
        }

        public void ReadXml(XmlReader reader)
        {
            reader.ReadStartElement("Asset");
            Input = (GameAsset)Serializer.ReadObject(reader);
            reader.ReadEndElement();
        }

        public void WriteXml(XmlWriter writer)
        {
            writer.WriteStartElement("Asset");
            Serializer.WriteObject(writer, Input);
            writer.WriteEndElement();
        }
        #endregion
    }
}
