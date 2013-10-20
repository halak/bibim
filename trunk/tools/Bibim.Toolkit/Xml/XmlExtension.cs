using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Linq;

namespace Bibim.Xml
{
    public static class XmlExtension
    {
        public static XmlElement FindElementByTagName(this XmlElement element, string name)
        {
            return GetFirstElementOrNull(element.GetElementsByTagName(name));
        }

        public static XmlElement FindElementByTagName(this XmlElement element, string localName, string namespaceURI)
        {
            return GetFirstElementOrNull(element.GetElementsByTagName(localName, namespaceURI));
        }

        private static XmlElement GetFirstElementOrNull(XmlNodeList elements)
        {
            if (elements != null && elements.Count > 0)
                return (XmlElement)elements[0];
            else
                return null;
        }

        public static Dictionary<string, object> LoadPList(string filename)
        {
            XDocument document = null;
            using (var stream = new FileStream(filename, FileMode.Open, FileAccess.Read))
                document = XDocument.Load(stream);

            var plist = document.Element("plist");
            var o = new Dictionary<string, object>();
            var current = (XElement)plist.Element("dict").FirstNode;
            do
            {
                string key = current.Value;
                current = (XElement)current.NextNode;

                string type = current.Name.ToString();
                switch (type.ToLower())
                {
                    case "integer":
                        o[key] = int.Parse(current.Value);
                        break;
                    case "real":
                        o[key] = float.Parse(current.Value);
                        break;
                    case "string":
                        o[key] = current.Value;
                        break;
                }
                current = (XElement)current.NextNode;

            } while (current != null);

            return o;
        }
    }
}
