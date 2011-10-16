using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

namespace Halak.Bibim.Asset.Pipeline.Recipes
{
    public sealed class ImportPhotoshopDocument : CookingNode<PhotoshopDocument>
    {
        #region Properties
        [XmlElement]
        public CookingNode<Stream> Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public ImportPhotoshopDocument()
        {
        }

        public ImportPhotoshopDocument(CookingNode<Stream> input)
        {
            Input = input;
        }
        #endregion

        #region Methods
        public override PhotoshopDocument Cook(CookingContext context)
        {
            using (var stream = Input.Cook(context))
                return new PhotoshopDocument(stream);
        }
        #endregion
    }
}
