using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Graphics
{
    public sealed class CookingSourceTexture2D
    {
        #region Properties
        public SourceTexture2D Texture
        {
            get;
            set;
        }

        public byte[] Buffer
        {
            get;
            set;
        }

        public int Pitch
        {
            get;
            set;
        }
        #endregion

        #region Constructor
        public CookingSourceTexture2D()
            : this(null, null, 0)
        {
        }

        public CookingSourceTexture2D(SourceTexture2D texture, byte[] buffer, int pitch)
        {
            Texture = texture;
            Buffer = buffer;
            Pitch = pitch;
        }
        #endregion
    }
}
