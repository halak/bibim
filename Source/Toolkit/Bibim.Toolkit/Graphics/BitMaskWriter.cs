using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;

namespace Bibim.Graphics
{
    [GameAssetWriter(typeof(BitMask))]
    public sealed class BitMaskWriter : GameAssetWriter<BitMask>
    {
        public override void Write(AssetStreamWriter writer, BitMask asset)
        {
            writer.Write(asset.ClassID);
            writer.Write((short)asset.Width);
            writer.Write((short)asset.Height);
            writer.Write((short)asset.Pitch);
            writer.Write(asset.Buffer);
        }
    }
}
