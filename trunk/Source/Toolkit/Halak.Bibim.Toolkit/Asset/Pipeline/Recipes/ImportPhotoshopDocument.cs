using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

namespace Halak.Bibim.Asset.Pipeline.Recipes
{
    public sealed class ImportPhotoshopDocument : CookableItem<PhotoshopDocument>
    {
        #region Properties
        [XmlElement]
        public ICookable<Stream> Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public ImportPhotoshopDocument()
        {
        }

        public ImportPhotoshopDocument(ICookable<Stream> input)
        {
            Input = input;
        }
        #endregion

        #region Methods
        public override PhotoshopDocument Cook(CookingContext context)
        {
            Stream stream = Input.Cook(context);

            return null;
        }
        #endregion
    }
}
