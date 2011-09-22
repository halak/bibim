using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Asset.Pipeline.Recipes
{
    public sealed class BitmapToTexture2D : CookableItem<object>
    {
        #region Properties
        public ICookable<Bitmap> Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public BitmapToTexture2D()
            : this(null)
        {
        }

        public BitmapToTexture2D(ICookable<Bitmap> input)
        {
            Input = input;
        }
        #endregion

        #region Methods
        public override object Cook(CookingContext context)
        {
            throw new NotImplementedException();
        }
        #endregion
    }
}
