using System;
using Bibim.Asset;
using Bibim.IO;
using Microsoft.Xna.Framework;

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
