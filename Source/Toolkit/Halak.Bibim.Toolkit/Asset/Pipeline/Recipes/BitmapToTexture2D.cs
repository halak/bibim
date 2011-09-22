using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using Halak.Bibim.Graphics;
using G = System.Drawing.Graphics;

namespace Halak.Bibim.Asset.Pipeline.Recipes
{
    public sealed class BitmapToTexture2D : CookingNode<SourceTexture2D>
    {
        #region Properties
        public CookingNode<Bitmap> Input
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

        public BitmapToTexture2D(CookingNode<Bitmap> input)
        {
            Input = input;
        }
        #endregion

        #region Methods
        public override SourceTexture2D Cook(CookingContext context)
        {
            Bitmap input = Input.Cook(context);
            int originalWidth = input.Width;
            int originalHeight = input.Height;

            int textureWidth = MathExtension.GetNearestPowerOfTwo(originalWidth);
            int textureHeight = MathExtension.GetNearestPowerOfTwo(originalHeight);

            if (originalWidth != textureWidth || originalHeight != textureHeight)
            {
                Bitmap textureBitmap = new Bitmap(textureWidth, textureHeight);
                G g = G.FromImage(textureBitmap);

                g.Clear(Color.Transparent);
                g.DrawImage(input, Point.Empty);
                g.Dispose();

                input = textureBitmap;
            }

            SourceTexture2D output = new SourceTexture2D();

            return output;
        }
        #endregion
    }
}
