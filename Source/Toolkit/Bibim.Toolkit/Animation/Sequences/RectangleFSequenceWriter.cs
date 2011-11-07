using System;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(RectFSequence))]
    public sealed class RectangleFSequenceWriter : SequenceWriterTemplate<RectFSequence, RectangleF>
    {
        protected override void WriteValue(AssetStreamWriter writer, RectangleF value)
        {
            writer.Write(value);
        }
    }
}
