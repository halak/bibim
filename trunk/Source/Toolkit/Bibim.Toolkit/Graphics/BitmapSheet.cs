using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Drawing;
using System.Text;
using GDIGraphics = System.Drawing.Graphics;

namespace Bibim.Graphics
{
    public sealed class BitmapSheet : IDisposable
    {
        #region Element (Nested Struct)
        public struct Element
        {
            public static Element Empty = new Element();

            public readonly Bitmap Sheet;
            public readonly Bitmap Source;
            public readonly Rectangle Bounds;
            public readonly Image.Transform AppliedTransform;

            public Element(Bitmap sheet, Bitmap source, Rectangle bounds, Image.Transform appliedTransform)
            {
                Sheet = sheet;
                Source = source;
                Bounds = bounds;
                AppliedTransform = appliedTransform;
            }
        }
        #endregion

        #region Options (Nested Enum)
        [Flags]
        public enum Options
        {
            None,
            PowerOfTwoSize = (1 << 0),
            RotatableMerging = (1 << 1)
        }
        #endregion

        #region Fields
        private Bitmap[] sheets;
        private List<Element> elements;
        private ReadOnlyCollection<Bitmap> readonlySheets;
        private ReadOnlyCollection<Element> readonlyElements;
        #endregion

        #region Properties
        public ICollection<Bitmap> Sheets
        {
            get { return readonlySheets; }
        }

        public ICollection<Element> Elements
        {
            get { return readonlyElements; }
        }

        public Element this[Bitmap key]
        {
            get
            {
                foreach (Element item in elements)
                {
                    if (item.Source == key)
                        return item;
                }

                return Element.Empty;
            }
        }
        #endregion

        #region Constructors
        private BitmapSheet(Bitmap[] sheets, List<Element> elements)
        {
            this.sheets = sheets;
            this.elements = elements;
            this.readonlySheets = new ReadOnlyCollection<Bitmap>(this.sheets);
            this.readonlyElements = new ReadOnlyCollection<Element>(this.elements);
        }
        #endregion

        #region Create (Methods)
        public static BitmapSheet Create(IEnumerable<Bitmap> input)
        {
            return Create(input, 1024, 1024, 16, 16, Options.None);
        }

        public static BitmapSheet Create(IEnumerable<Bitmap> input, int maxWidth, int maxHeight, Options options)
        {
            return Create(input, maxWidth, maxHeight, (maxWidth >= 16) ? 16 : 1, (maxHeight >= 16) ? 16 : 1, options);
        }

        public static BitmapSheet Create(IEnumerable<Bitmap> input, int maxWidth, int maxHeight, int clusterSize, Options options)
        {
            return Create(input, maxWidth, maxHeight, clusterSize, clusterSize, options);
        }

        public static BitmapSheet Create(IEnumerable<Bitmap> input, int maxWidth, int maxHeight, int clusterWidth, int clusterHeight, Options options)
        {
            if (input == null)
                throw new ArgumentNullException("input");
            if (maxWidth <= 0)
                throw new ArgumentException("maxWidth");
            if (maxHeight <= 0)
                throw new ArgumentException("maxHeight");

            #region maxWidth/maxHeight를 2의 멱수로 맞춥니다.
            if (options.HasFlag(Options.PowerOfTwoSize))
            {
                // maxWidth/maxHeight보다 작은 2의 멱수로 맞춥니다.
                int mw = MathExtension.GetNearestPowerOfTwo(maxWidth);
                int mh = MathExtension.GetNearestPowerOfTwo(maxHeight);

                if (maxWidth != mw)
                    maxWidth = mw / 2;
                if (maxHeight != mh)
                    maxHeight = mh / 2;
            }
            #endregion

            foreach (Bitmap item in input)
            {
                if (item.Width >= maxWidth || item.Height >= maxHeight)
                    throw new ArgumentException("input");
            }

            // Bitmap들을 크기가 큰 순으로 정렬합니다.
            var sortedInput = new List<Bitmap>(input);
            sortedInput.Sort((a, b) =>
            {
                // 가로와 세로를 각각 제곱을 하면서 한 방향이 지나치게 클 경우 큰 이미지로 인식하게 합니다.
                int aWeight = (a.Width * a.Width) + (a.Height * a.Height);
                int bWeight = (b.Width * b.Width) + (b.Height * b.Height);
                return bWeight.CompareTo(aWeight);
            });

            var items = new List<Tuple<int, Bitmap, Rectangle, Image.Transform>>();
            int margin = 1;
            var textureAtlases = new List<RectangleStorage>();
            #region 각각의 Bitmap들을 어떤 큰 Bitmap에 배치할지 결정합니다. (선작업)
            foreach (Bitmap item in sortedInput)
            {
                // 실제로는 여백을 추가한 크기로 할당합니다.
                int aw = margin + item.Width + margin;
                int ah = margin + item.Height + margin;

                RectangleStorage atlas = null;

                int index = -1;
                if (options.HasFlag(Options.RotatableMerging))
                {
                    // 병합할 때 변환 가능 Option이 설정되어 있으면 가로 세로를 바꾼 영역도 검색해봅니다.
                    index = textureAtlases.FindIndex((ta) => ta.CanAllocate(aw, ah) || ta.CanAllocate(ah, aw));
                }
                else
                    index = textureAtlases.FindIndex((ta) => ta.CanAllocate(aw, ah));

                if (index != -1)
                    atlas = textureAtlases[index];
                else
                {
                    atlas = new RectangleStorage(maxWidth, maxHeight, clusterWidth, clusterHeight);
                    index = textureAtlases.Count;
                    textureAtlases.Add(atlas);
                }

                Rectangle rectangle = atlas.Allocate(aw, ah);
                Image.Transform appliedTransform = Image.Transform.Identity;
                if (rectangle.IsEmpty)
                {
                    Debug.Assert(options.HasFlag(Options.RotatableMerging));
                    rectangle = atlas.Allocate(ah, aw);
                    appliedTransform = Image.Transform.RotateCW90;
                }

                Rectangle bitmapRectangle = Rectangle.FromLTRB(rectangle.Left + margin,
                                                               rectangle.Top + margin,
                                                               rectangle.Right - margin,
                                                               rectangle.Bottom - margin);
                items.Add(Tuple.Create(index, item, bitmapRectangle, appliedTransform));
            }
            #endregion

            var graphics = new GDIGraphics[textureAtlases.Count];
            var sheetBitmaps = new Bitmap[textureAtlases.Count];
            var elements = new List<Element>();
            #region 입력된 작은 Bitmap들을 큰 SheetBitmap에 복사합니다.
            foreach (var item in items)
            {
                int sheetIndex = item.Item1;
                Bitmap bitmap = item.Item2;
                Rectangle rectangle = item.Item3;
                Image.Transform appliedTransform = item.Item4;

                if (sheetBitmaps[sheetIndex] == null)
                {
                    Rectangle bounds = textureAtlases[item.Item1].GetBounds();
                    Debug.Assert(bounds.X == 0 && bounds.Y == 0);

                    int w = bounds.Width;
                    int h = bounds.Height;
                    if (options.HasFlag(Options.PowerOfTwoSize))
                    {
                        w = MathExtension.GetNearestPowerOfTwo(w);
                        h = MathExtension.GetNearestPowerOfTwo(h);
                    }

                    sheetBitmaps[sheetIndex] = new Bitmap(w, h);
                    graphics[sheetIndex] = GDIGraphics.FromImage(sheetBitmaps[sheetIndex]);
                    graphics[sheetIndex].Clear(Color.Transparent);
                }

                switch (appliedTransform)
                {
                    case Image.Transform.Identity:
                        graphics[sheetIndex].DrawImageUnscaled(bitmap, rectangle.X, rectangle.Y);
                        
                        graphics[sheetIndex].DrawImage(bitmap, rectangle.Left - 1, rectangle.Top, new Rectangle(0, 0, 1, rectangle.Height), GraphicsUnit.Pixel);
                        graphics[sheetIndex].DrawImage(bitmap, rectangle.Right, rectangle.Top, new Rectangle(bitmap.Width - 1, 0, 1, rectangle.Height), GraphicsUnit.Pixel);
                        graphics[sheetIndex].DrawImage(bitmap, rectangle.Left, rectangle.Top - 1, new Rectangle(0, 0, rectangle.Width, 1), GraphicsUnit.Pixel);
                        graphics[sheetIndex].DrawImage(bitmap, rectangle.Left, rectangle.Bottom, new Rectangle(0, bitmap.Height - 1, rectangle.Width, 1), GraphicsUnit.Pixel);

                        var sheetBitmap = sheetBitmaps[sheetIndex];
                        sheetBitmap.SetPixel(rectangle.Left - 1, rectangle.Top - 1, sheetBitmap.GetPixel(rectangle.Left, rectangle.Top));
                        sheetBitmap.SetPixel(rectangle.Right + 0, rectangle.Top - 1, sheetBitmap.GetPixel(rectangle.Right - 1, rectangle.Top));
                        sheetBitmap.SetPixel(rectangle.Left - 1, rectangle.Bottom + 0, sheetBitmap.GetPixel(rectangle.Left, rectangle.Bottom - 1));
                        sheetBitmap.SetPixel(rectangle.Right + 0, rectangle.Bottom + 0, sheetBitmap.GetPixel(rectangle.Right - 1, rectangle.Bottom - 1));
                        break;
                    case Image.Transform.RotateCW90:
                        graphics[sheetIndex].TranslateTransform(+rectangle.X, +rectangle.Y);
                        graphics[sheetIndex].RotateTransform(90.0f);
                        graphics[sheetIndex].TranslateTransform(-rectangle.X, -rectangle.Y - rectangle.Width);
                        graphics[sheetIndex].DrawImageUnscaled(bitmap, rectangle.X, rectangle.Y);
                        graphics[sheetIndex].ResetTransform();
                        break;
                    default:
                        throw new NotSupportedException();
                }

                elements.Add(new Element(sheetBitmaps[sheetIndex], bitmap, rectangle, appliedTransform));
            }
            #endregion

            #region 생성한 Graphics 객체를 Dispose합니다.
            foreach (var item in graphics)
            {
                if (item != null)
                    item.Dispose();
            }
            #endregion

            return new BitmapSheet(sheetBitmaps, elements);
        }
        #endregion

        #region Methods
        public void Dispose()
        {
            foreach (Bitmap item in sheets)
                item.Dispose();

            sheets = null;
            elements.Clear();
            readonlySheets = null;
            readonlyElements = null;

            GC.SuppressFinalize(this);
        }
        #endregion
    }
}
