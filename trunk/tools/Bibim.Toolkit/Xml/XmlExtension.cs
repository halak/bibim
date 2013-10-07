using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

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
    }
}
