using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

namespace Halak.Bibim.Asset.Pipeline.Recipes
{
    public sealed class FileToStream : CookableItem<Stream>
    {
        #region Fields
        private string input;
        #endregion

        #region Properties
        [XmlAttribute]
        public string Input
        {
            get { return input; }
            set
            {
                input = value ?? string.Empty;
            }
        }
        #endregion

        #region Constructors
        public FileToStream()
            : this(string.Empty)
        {
        }

        public FileToStream(string input)
        {
            Input = input;
        }
        #endregion

        #region Methods
        public override Stream Cook(CookingContext context)
        {
            string path = context.ExpandVariables(Input);
            return new FileStream(path, FileMode.Open, FileAccess.Read);
        }
        #endregion
    }
}
