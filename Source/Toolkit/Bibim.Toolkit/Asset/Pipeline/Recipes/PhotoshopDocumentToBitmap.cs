using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class PhotoshopDocumentToBitmap : CookingNode<Bitmap>
    {
        #region Properties
        public CookingNode<PhotoshopDocument> Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public PhotoshopDocumentToBitmap()
        {
        }

        public PhotoshopDocumentToBitmap(CookingNode<PhotoshopDocument> input)
        {
            Input = input;
        }
        #endregion

        #region Methods
        public override Bitmap Cook(CookingContext context)
        {
            PhotoshopDocument input = Input.Cook(context);
            if (input == null)
                return null;

            return input.MergedBitmap;
        }
        #endregion
    }
}
