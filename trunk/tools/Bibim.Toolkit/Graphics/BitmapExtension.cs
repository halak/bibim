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

        public static Bitmap Clip(this Bitmap input, Rectangle rectangle)
        {
            if (rectangle.Width <= 0 || rectangle.Height <= 0)
                return null;

            var result = new Bitmap(rectangle.Width, rectangle.Height);
            using (var g = GDIGraphics.FromImage(result))
            {
                g.DrawImage(input,
                            new System.Drawing.Rectangle(0, 0, result.Width, result.Height),
                            rectangle,
                            GraphicsUnit.Pixel);
            }

            return result;
        }

        public static Bitmap ClipAndDispose(this Bitmap input, Rectangle rectangle)
        {
            var output = Clip(input, rectangle);
            input.Dispose();
            return output;
        }

        public static Rectangle GetTrimmedRect(this Bitmap input)
        {
            return input.GetTrimmedRect(new Rectangle(0, 0, input.Width, input.Height), Color.Transparent);
        }

        public static Rectangle GetTrimmedRect(this Bitmap input, Rectangle rectangle)
        {
            return input.GetTrimmedRect(rectangle, Color.Transparent);
        }

        public static Rectangle GetTrimmedRect(this Bitmap input, Color testColor)
        {
            return input.GetTrimmedRect(new Rectangle(0, 0, input.Width, input.Height), testColor);
        }

        public static Rectangle GetTrimmedRect(this Bitmap input, Rectangle rectangle, Color testColor)
        {
            Func<Bitmap, int, int, int, bool> testHorzLine = IsHorizontalLineTransparent;
            Func<Bitmap, int, int, int, bool> testVertLine = IsVerticalLineTransparent;
            if (testColor.A > 0)
            {
                testHorzLine = (bitmap, x0, x1, y) => IsHorizontalLineAll(bitmap, x0, x1, y, testColor);
                testVertLine = (bitmap, y0, y1, x) => IsVerticalLineAll(bitmap, y0, y1, x, testColor);
            }

            int left = rectangle.Left;
            int top = rectangle.Top;
            int right = rectangle.Right;
            int bottom = rectangle.Bottom;
            bool changed = false;

            do
            {
                changed = false;
                while (testHorzLine(input, left, right, top))
                {
                    top++;
                    changed = true;
                }

                while (testHorzLine(input, left, right, bottom - 1))
                {
                    bottom--;
                    changed = true;
                }

                while (testVertLine(input, top, bottom, left))
                {
                    left++;
                    changed = true;
                }

                while (testVertLine(input, top, bottom, right - 1))
                {
                    right--;
                    changed = true;
                }
            } while (changed);

            return new Rectangle(left, top, right - left, bottom - top);
        }

        private static bool IsHorizontalLineTransparent(Bitmap bitmap, int x0, int x1, int y)
        {
            for (int x = x0; x < x1; x++)
            {
                if (bitmap.GetPixel(x, y).A != 0)
                    return false;
            }

            return true;
        }

        private static bool IsVerticalLineTransparent(Bitmap bitmap, int y0, int y1, int x)
        {
            for (int y = y0; y < y1; y++)
            {
                if (bitmap.GetPixel(x, y).A != 0)
                    return false;
            }

            return true;
        }


        private static bool IsHorizontalLineAll(Bitmap bitmap, int x0, int x1, int y, Color color)
        {
            var argb = color.ToArgb();
            for (int x = x0; x < x1; x++)
            {
                if (bitmap.GetPixel(x, y).ToArgb() != argb)
                    return false;
            }

            return true;
        }

        private static bool IsVerticalLineAll(Bitmap bitmap, int y0, int y1, int x, Color color)
        {
            var argb = color.ToArgb();
            for (int y = y0; y < y1; y++)
            {
                if (bitmap.GetPixel(x, y).ToArgb() != argb)
                    return false;
            }

            return true;
        }
    }
}
