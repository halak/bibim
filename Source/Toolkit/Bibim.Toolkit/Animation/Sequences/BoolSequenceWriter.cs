using System;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(BoolSequence))]
    public sealed class BoolSequenceWriter : SequenceWriterTemplate<BoolSequence, bool>
    {
        public override void WriteValue(AssetStreamWriter writer, bool value)
        {
            writer.Write(value);
        }
    }
}
