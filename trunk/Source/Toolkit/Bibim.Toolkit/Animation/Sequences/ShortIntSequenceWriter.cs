using System;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(ShortIntSequence))]
    public sealed class ShortIntSequenceWriter : SequenceWriterTemplate<ShortIntSequence, short>
    {
        public override void WriteValue(AssetStreamWriter writer, short value)
        {
            writer.Write(value);
        }
    }
}
