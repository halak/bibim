using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace Halak.Bibim.Graphics
{
    public sealed class SourceTexture2DCookingTag
    {
        #region Properties
        public int Pitch
        {
            get;
            set;
        }

        public byte[] Buffer
        {
            get;
            set;
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
        #endregion
    }
}
