using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Diagnostics;

namespace Bibim.Graphics
{
    public sealed class SourceTexture2DCookingTag
    {
        #region Properties
        public int Pitch
        {
            get;
            private set;
        }

        public byte[] Buffer
        {
            get;
            private set;
        }

        public Bitmap Bitmap
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public SourceTexture2DCookingTag()
        {
        }

        public SourceTexture2DCookingTag(int pitch, byte[] buffer)
        {
            Debug.Assert(pitch >= 0);

            Pitch = pitch;
            Buffer = buffer;
        }

        public SourceTexture2DCookingTag(Bitmap bitmap)
        {
            Bitmap = bitmap;
        }
        #endregion
    }
}
