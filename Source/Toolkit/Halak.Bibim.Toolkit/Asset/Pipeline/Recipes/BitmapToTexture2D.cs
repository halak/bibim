using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Asset.Pipeline.Recipes
{
    public sealed class BitmapToTexture2D : AssetRecipe
    {
        #region Fields
        private string input;
        private string output;
        #endregion

        #region Properties
        public string Input
        {
            get { return input; }
            set
            {
                input = value ?? string.Empty;
            }
        }

        public string Output
        {
            get { return output; }
            set
            {
                output = value ?? string.Empty;
            }
        }
        #endregion

        #region Constructors
        public BitmapToTexture2D()
            : this(string.Empty, string.Empty)
        {
        }

        public BitmapToTexture2D(string input, string output)
        {
            this.input = input ?? string.Empty;
            this.output = output ?? string.Empty;
        }
        #endregion

        #region Methods
        public override void Cook(CookingContext context)
        {
            string actualInput = context.ExpandVariables(Input);
            string actualOutput = context.ExpandVariables(Output);

            Bitmap inputBitmap = (Bitmap)context.GetIngredient(actualInput);
        }
        #endregion
    }
}
