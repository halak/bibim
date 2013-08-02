using System;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(LongIntSequence))]
    public sealed class LongIntSequenceWriter : SequenceWriterTemplate<LongIntSequence, long>
    {
        protected override void WriteValue(AssetStreamWriter writer, long value)
        {
            writer.Write(value);
        }
    }
}
