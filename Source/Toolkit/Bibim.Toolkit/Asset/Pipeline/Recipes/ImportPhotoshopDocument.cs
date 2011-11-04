using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

namespace Bibim.Asset.Pipeline.Recipes
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

        [XmlAttribute]
        public bool IgnoreImageResources
        {
            get;
            set;
        }

        [XmlAttribute]
        public bool IgnoreLayers
        {
            get;
            set;
        }

        [XmlAttribute]
        public bool IgnoreMergedBitmap
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public ImportPhotoshopDocument()
            : this(null, false, false, false)
        {
        }

        public ImportPhotoshopDocument(CookingNode<Stream> input)
            : this(input, false, false, false)
        {
        }

        public ImportPhotoshopDocument(CookingNode<Stream> input, bool ignoreImageResources, bool ignoreLayers, bool ignoreMergedBitmap)
        {
            Input = input;
            IgnoreImageResources = ignoreImageResources;
            IgnoreLayers = ignoreLayers;
            IgnoreMergedBitmap = ignoreMergedBitmap;
        }
        #endregion

        #region Methods
        public override PhotoshopDocument Cook(CookingContext context)
        {
            using (var stream = Input.Cook(context))
                return new PhotoshopDocument(stream, IgnoreImageResources, IgnoreLayers, IgnoreMergedBitmap);
        }
        #endregion
    }
}
