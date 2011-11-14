using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using Bibim.Graphics;
using G = System.Drawing.Graphics;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class BitmapToMaskTexture2D : CookingNode<SourceTexture2D>
    {
        #region Properties
        public CookingNode<Bitmap> Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public BitmapToMaskTexture2D()
            : this(null)
        {
        }

        public BitmapToMaskTexture2D(CookingNode<Bitmap> input)
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
                g.DrawImage(input,
                            new Rectangle(0, 0, input.Width, input.Height),
                            new Rectangle(0, 0, input.Width, input.Height),
                            GraphicsUnit.Pixel);
                g.Dispose();

                input = textureBitmap;
            }

            SourceTexture2D output = new SourceTexture2D(null, originalWidth, originalHeight, input.Width, input.Height, Texture2D.PixelFormat.A8);
            byte[] buffer = new byte[input.Width * input.Height];
            for (int y = 0; y < input.Height; y++)
            {
                for (int x = 0; x < input.Width; x++)
                    buffer[(y * input.Height) + x] = input.GetPixel(x, y).R;
            }

            output.Tag = new SourceTexture2DCookingTag(input.Width, buffer);

            return output;
        }
        #endregion
    }
}
