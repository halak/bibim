using System;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(DoubleSequence))]
    public sealed class DoubleSequenceWriter : SequenceWriterTemplate<DoubleSequence, double>
    {
        public override void WriteValue(AssetStreamWriter writer, double value)
        {
            writer.Write(value);
        }
    }
}
