using System;
using System.Drawing;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(RectSequence))]
    public sealed class RectangleSequenceWriter : SequenceWriterTemplate<RectSequence, Rectangle>
    {
        protected override void WriteValue(AssetStreamWriter writer, Rectangle value)
        {
            writer.Write(value);
        }
    }
}
