using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Asset
{
    [ClassID('S', 'T', 'G', 'A')]
    public sealed class StreamingGameAsset : GameAsset
    {
        private byte[] data;

        public byte[] Data
        {
            get { return data; }
            set
            {
                data = value ?? new byte[0];
            }
        }

        public StreamingGameAsset()
            : this(null)
        {
        }

        public StreamingGameAsset(byte[] data)
        {
            Data = data;
        }
    }
}
