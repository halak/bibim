using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class ImportPhotoshopDocument : CookingNode<PhotoshopDocument>
    {
        #region Properties
        public CookingNode<Stream> Input
        {
            get;
            set;
        }

        public double Scale
        {
            get;
            set;
        }

        public bool IgnoreImageResources
        {
            get;
            set;
        }

        public bool IgnoreLayers
        {
            get;
            set;
        }

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
            Scale = 1.0;
        }
        #endregion

        #region Methods
        public override PhotoshopDocument Cook(CookingContext context)
        {
            using (var stream = Input.Cook(context))
            {
                var document = new PhotoshopDocument(stream, IgnoreImageResources, IgnoreLayers, IgnoreMergedBitmap);
                if (Scale != 1.0)
                    document.Scale(Scale, Scale);
                
                return document;
            }
        }
        #endregion
    }
}
