using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;

namespace Bibim.Graphics
{
    [ClassID('B', 'I', 'T', 'M')]
    public sealed class BitMask : GameAsset
    {
        public int Width
        {
            get;
            set;
        }

        public int Height
        {
            get;
            set;
        }

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

        public BitMask()
            : this(0, 0, 0, null)
        {
        }

        public BitMask(int width, int height, int pitch, byte[] buffer)
        {
            Width = width;
            Height = height;
            Pitch = pitch;
            Buffer = buffer;
        }

        public class Reader : GameAssetReader<BitMask>
        {
            public override BitMask Read(AssetStreamReader reader, BitMask existingInstance)
            {
                throw new NotImplementedException();
            }
        }
    }
}
