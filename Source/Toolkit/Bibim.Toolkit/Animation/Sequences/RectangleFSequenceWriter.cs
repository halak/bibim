using System;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(RectangleFSequence))]
    public sealed class RectangleFSequenceWriter : SequenceWriterTemplate<RectangleFSequence, RectangleF>
    {
        public override void WriteValue(AssetStreamWriter writer, RectangleF value)
        {
            writer.Write(value);
        }
    }
}
