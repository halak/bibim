using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using Bibim.Graphics;
using FreeImageAPI;
using G = System.Drawing.Graphics;
using Encoder = System.Drawing.Imaging.Encoder;

namespace Bibim.Asset.Pipeline.Recipes
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
                g.DrawImage(input,
                            new Rectangle(0, 0, input.Width, input.Height),
                            new Rectangle(0, 0, input.Width, input.Height),
                            GraphicsUnit.Pixel);
                g.Dispose();

                input = textureBitmap;
            }

            SourceTexture2D output = new SourceTexture2D(null, originalWidth, originalHeight, input.Width, input.Height, Texture2D.PixelFormat.A8R8G8B8);

            int bytesPerPixel = 4;
            var swappedBitmap = CreateRedBlueSwappedBitmap(input);
            byte[] pngBuffer = GeneratePNGBuffer(swappedBitmap);
            swappedBitmap.Dispose();

            if (pngBuffer.Length <= input.Width * bytesPerPixel * input.Height)
            {
                output.Tag = new SourceTexture2DCookingTag(input.Width * bytesPerPixel,
                                                           SourceTexture2DCookingTag.CompressionType.Png,
                                                           pngBuffer);
            }
            else
            {
                BitmapData bitmapData = input.LockBits(new Rectangle(0, 0, input.Width, input.Height), ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);

                byte[] buffer = new byte[bitmapData.Stride * bitmapData.Height];
                Marshal.Copy(bitmapData.Scan0, buffer, 0, buffer.Length);

                output.Tag = new SourceTexture2DCookingTag(bitmapData.Stride, buffer);

                input.UnlockBits(bitmapData);
            }

            return output;
        }

        private static readonly ColorMatrix redBlueSwappingColorMatrix = new ColorMatrix(new float[][] {
            new float[]{1, 0, 0, 0, 0},
            new float[]{0, 1, 0, 0, 0},
            new float[]{0, 0, 1, 0, 0},
            new float[]{0, 0, 0, 1, 0},
            new float[]{0, 0, 0, 0, 1},
        });
        public static Bitmap CreateRedBlueSwappedBitmap(Bitmap original)
        {
            Bitmap result = new Bitmap(original.Width, original.Height);

            using (var g = G.FromImage(result))
            {
                ImageAttributes attributes = new ImageAttributes();
                attributes.SetColorMatrix(redBlueSwappingColorMatrix);

                g.DrawImage(original,
                            new Rectangle(0, 0, result.Width, result.Height),
                            0, 0, original.Width, original.Height,
                            GraphicsUnit.Pixel,
                            attributes);
            }

            return result;
        }

        public static byte[] GeneratePNGBuffer(Bitmap original)
        {
            using (var stream = new MemoryStream(original.Width * 4 * original.Height / 8))
            using (var freeImage = new FreeImageBitmap(original))
            {
                freeImage.Save(stream, FREE_IMAGE_FORMAT.FIF_PNG, FREE_IMAGE_SAVE_FLAGS.PNG_Z_BEST_COMPRESSION);
                return stream.GetBuffer();
            }
        }
        #endregion
    }
}
