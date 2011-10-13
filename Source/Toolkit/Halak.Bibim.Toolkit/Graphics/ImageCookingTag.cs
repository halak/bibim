using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Graphics
{
    public sealed class ImageCookingTag
    {
        #region Properties
        public Bitmap Bitmap
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public ImageCookingTag()
        {
        }

        public ImageCookingTag(Bitmap bitmap)
        {
            Bitmap = bitmap;
        }
        #endregion
    }
}
