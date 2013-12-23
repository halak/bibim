using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.IO;
using System.Linq;
using System.Text;
using GDIGraphics = System.Drawing.Graphics;

namespace Bibim.Graphics
{
    public static class BitmapExtension
    {
        public static Bitmap CreateOne(params string[] paths)
        {
            Bitmap bitmap = null;
            foreach (var item in paths)
            {
                if (File.Exists(item) == false)
                    continue;

                try
                {
                    bitmap = new Bitmap(item);
                }
                catch (ArgumentException)
                {
                    continue;
                }

                if (bitmap != null)
                    return bitmap.ResizeAndDispose(bitmap.Width, bitmap.Height);
            }

            return null;
        }

        public static Bitmap Resize(this Bitmap input, int width, int height, bool autoDispose = false)
        {
            if (input == null)
                throw new ArgumentNullException("input");
            if (width <= 0)
                throw new ArgumentException("must be greater than 0", "width");
            if (height <= 0)
                throw new ArgumentException("must be greater than 0", "height");

            Bitmap resizedBitmap = new Bitmap(width, height);
            using (GDIGraphics g = GDIGraphics.FromImage(resizedBitmap))
            {
                g.SmoothingMode = SmoothingMode.HighQuality;
                g.InterpolationMode = InterpolationMode.HighQualityBicubic;
                g.CompositingQuality = CompositingQuality.HighQuality;
                g.DrawImage(input, 0, 0, width, height);
            }

            if (autoDispose)
                input.Dispose();

            return resizedBitmap;
        }

        public static Bitmap ResizeAndDispose(this Bitmap input, int width, int height)
        {
            return Resize(input, width, height, true);
        }
    }
}
