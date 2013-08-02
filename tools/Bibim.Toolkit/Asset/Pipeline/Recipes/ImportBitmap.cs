using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Text;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class ImportBitmap : CookingNode<Bitmap>
    {
        #region Properties
        public CookingNode<Stream> Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public ImportBitmap()
            : this(null)
        {
        }

        public ImportBitmap(CookingNode<Stream> input)
        {
            Input = input;
        }
        #endregion

        #region Methods
        public override Bitmap Cook(CookingContext context)
        {
            using (var stream = Input.Cook(context))
                return new Bitmap(stream);
        }
        #endregion
    }
}
