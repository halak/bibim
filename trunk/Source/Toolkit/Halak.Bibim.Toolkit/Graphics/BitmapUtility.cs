using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Graphics
{
    public static class BitmapUtility
    {
        #region Pack
        public static Bitmap[] Pack(IEnumerable<Bitmap> input)
        {
            return Pack(input, int.MaxValue, int.MaxValue);
        }

        public static Bitmap[] Pack(IEnumerable<Bitmap> input, int maxWidth, int maxHeight)
        {
            if (input == null)
                throw new ArgumentNullException("input");
            if (maxWidth <= 0)
                throw new ArgumentException("maxWidth");
            if (maxHeight <= 0)
                throw new ArgumentException("maxHeight");

            IEnumerable<Bitmap> arrangedInput = null;
            Size[] sizes = null;
            GuessPackingProcess(input, maxWidth, maxHeight, out arrangedInput, out sizes);
 
            Bitmap[] output = new Bitmap[sizes.Length];
            int outputIndex = 0;
            foreach (Bitmap item in arrangedInput)
            {
                if (output[outputIndex] == null)
                    output[outputIndex] = new Bitmap(sizes[outputIndex].Width, sizes[outputIndex].Height);

                if (0)
                    outputIndex++;
            }

            Trace.Assert(outputIndex == output.Length);

            return output;
        }

        private static void GuessPackingProcess(IEnumerable<Bitmap> input, int maxWidth, int maxHeight,
                                                out IEnumerable<Bitmap> arrangedInput, out Size[] sizes)
        {
            arrangedInput = null;
            sizes = null;
        }
        #endregion
    }
}
