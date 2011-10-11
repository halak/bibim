using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Xml.Serialization;
using Halak.Bibim.Graphics;
using G = System.Drawing.Graphics;

namespace Halak.Bibim.Asset.Pipeline.Recipes
{
    public sealed class BitmapToTexture2D : CookingNode<SourceTexture2D>
    {
        #region Properties
        [XmlElement]
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

            SourceTexture2D output = new SourceTexture2D(null, originalWidth, originalHeight, input.Width, input.Height);

            BitmapData bitmapData = input.LockBits(new Rectangle(0, 0, input.Width, input.Height), ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);
            byte[] buffer = new byte[bitmapData.Stride * bitmapData.Height];
            Marshal.Copy(bitmapData.Scan0, buffer, 0, buffer.Length);
            output.Tag = new SourceTexture2DCookingTag(bitmapData.Stride, buffer);
            input.UnlockBits(bitmapData);

            return output;
        }
        #endregion
    }
}
