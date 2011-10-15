using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using GDIGraphics = System.Drawing.Graphics;

namespace Halak.Bibim.Graphics
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

            public Element(Bitmap sheet, Bitmap source, Rectangle bounds)
            {
                Sheet = sheet;
                Source = source;
                Bounds = bounds;
            }
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
            return Create(input, 1024, 1024, 16, 16, false);
        }

        public static BitmapSheet Create(IEnumerable<Bitmap> input, int maxWidth, int maxHeight, bool isPowerOfTwoSize)
        {
            return Create(input, maxWidth, maxHeight, (maxWidth >= 16) ? 16 : 1, (maxHeight >= 16) ? 16 : 1, false);
        }

        public static BitmapSheet Create(IEnumerable<Bitmap> input, int maxWidth, int maxHeight, int clusterSize, bool isPowerOfTwoSize)
        {
            return Create(input, maxWidth, maxHeight, clusterSize, clusterSize, false);
        }

        public static BitmapSheet Create(IEnumerable<Bitmap> input, int maxWidth, int maxHeight, int clusterWidth, int clusterHeight, bool isPowerOfTwoSize)
        {
            if (input == null)
                throw new ArgumentNullException("input");
            if (maxWidth <= 0)
                throw new ArgumentException("maxWidth");
            if (maxHeight <= 0)
                throw new ArgumentException("maxHeight");

            #region maxWidth/maxHeight를 2의 멱수로 맞춥니다.
            if (isPowerOfTwoSize)
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
                return (b.Width + b.Height).CompareTo(a.Width + a.Height);
            });

            var items = new List<Tuple<int, Bitmap, Rectangle>>();
            int margin = 1;
            var textureAtlases = new List<RectangleStorage>();
            #region 각각의 Bitmap들을 어떤 큰 Bitmap에 배치할지 결정합니다. (선작업)
            foreach (Bitmap item in sortedInput)
            {
                // 실제로는 여백을 추가한 크기로 할당합니다.
                int aw = margin + item.Width + margin;
                int ah = margin + item.Height + margin;

                RectangleStorage atlas = null;
                int index = textureAtlases.FindIndex((ta) => ta.CanAllocate(aw, ah));
                if (index != -1)
                    atlas = textureAtlases[index];
                else
                {
                    atlas = new RectangleStorage(maxWidth, maxHeight, clusterWidth, clusterHeight);
                    index = textureAtlases.Count;
                    textureAtlases.Add(atlas);
                }

                Rectangle rectangle = atlas.Allocate(aw, ah);
                Rectangle bitmapRectangle = Rectangle.FromLTRB(rectangle.Left + margin,
                                                               rectangle.Top + margin,
                                                               rectangle.Right - margin,
                                                               rectangle.Bottom - margin);
                items.Add(Tuple.Create(index, item, bitmapRectangle));
            }
            #endregion

            var graphics = new GDIGraphics[textureAtlases.Count];
            var sheetBitmaps = new Bitmap[textureAtlases.Count];
            var elements = new List<Element>();
            #region 입력된 작은 Bitmap들을 큰 Bitmap에 복사합니다.
            foreach (var item in items)
            {
                int sheetIndex = item.Item1;
                Bitmap bitmap = item.Item2;
                Rectangle rectangle = item.Item3;

                if (sheetBitmaps[sheetIndex] == null)
                {
                    Rectangle bounds = textureAtlases[item.Item1].GetBounds();
                    Debug.Assert(bounds.X == 0 && bounds.Y == 0);

                    int w = bounds.Width;
                    int h = bounds.Height;
                    if (isPowerOfTwoSize)
                    {
                        w = MathExtension.GetNearestPowerOfTwo(w);
                        h = MathExtension.GetNearestPowerOfTwo(h);
                    }

                    sheetBitmaps[sheetIndex] = new Bitmap(w, h);
                    graphics[sheetIndex] = GDIGraphics.FromImage(sheetBitmaps[sheetIndex]);
                    graphics[sheetIndex].Clear(Color.Transparent);
                }

                graphics[sheetIndex].DrawImageUnscaled(bitmap, rectangle.X, rectangle.Y);
                elements.Add(new Element(sheetBitmaps[sheetIndex], bitmap, rectangle));
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
