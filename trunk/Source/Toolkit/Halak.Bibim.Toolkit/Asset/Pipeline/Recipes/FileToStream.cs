using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

namespace Halak.Bibim.Asset.Pipeline.Recipes
{
    public sealed class FileToStream : CookingNode<Stream>
    {
        #region Properties
        [XmlAttribute]
        public string Input1
        {
            get;
            set;
        }

        [XmlAttribute]
        public string Input2
        {
            get;
            set;
        }

        [XmlAttribute]
        public string Input3
        {
            get;
            set;
        }

        [XmlAttribute]
        public string Input4
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public FileToStream()
        {
        }

        public FileToStream(string input)
        {
            Input1 = input;
        }

        public FileToStream(string input1, string input2, string input3, string input4)
        {
            Input1 = input1;
            Input2 = input2;
            Input3 = input3;
            Input4 = input4;
        }
        #endregion

        #region Methods
        public override Stream Cook(CookingContext context)
        {
            string[] paths = { Input1, Input2, Input3, Input4 };
            foreach (string item in paths)
            {
                string actualPath = Path.Combine(context.BaseDirectory, context.Directory, context.ExpandVariables(item));

                if (File.Exists(actualPath))
                    return new FileStream(actualPath, FileMode.Open, FileAccess.Read);
            }

            return null;
        }
        #endregion
    }
}
