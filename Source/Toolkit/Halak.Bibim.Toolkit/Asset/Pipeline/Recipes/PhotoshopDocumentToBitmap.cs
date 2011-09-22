using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

namespace Halak.Bibim.Asset.Pipeline.Recipes
{
    [XmlInclude(typeof(PhotoshopDocumentToBitmap))]
    public sealed class PhotoshopDocumentToBitmap : CookableItem<Bitmap>
    {
        #region Properties
        [XmlElement]
        public CookableItem<PhotoshopDocument> Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public PhotoshopDocumentToBitmap()
        {
        }

        public PhotoshopDocumentToBitmap(CookableItem<PhotoshopDocument> input)
        {
            Input = input;
        }
        #endregion

        #region Methods
        public override Bitmap Cook(CookingContext context)
        {
            //PhotoshopDocument input = Input.Cook(context);

            return null;
        }
        #endregion
    }
}
