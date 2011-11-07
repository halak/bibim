using System;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(IntSequence))]
    public sealed class IntSequenceWriter : SequenceWriterTemplate<IntSequence, int>
    {
        protected override void WriteValue(AssetStreamWriter writer, int value)
        {
            writer.Write(value);
        }
    }
}
