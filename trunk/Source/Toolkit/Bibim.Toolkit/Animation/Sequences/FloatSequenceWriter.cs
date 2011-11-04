using System;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(FloatSequence))]
    public sealed class FloatSequenceWriter : SequenceWriterTemplate<FloatSequence, float>
    {
        public override void WriteValue(AssetStreamWriter writer, float value)
        {
            writer.Write(value);
        }
    }
}
