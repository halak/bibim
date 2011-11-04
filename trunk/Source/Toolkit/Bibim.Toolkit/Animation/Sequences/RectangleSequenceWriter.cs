using System;
using Bibim.Asset;
using Bibim.IO;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(RectangleSequence))]
    public sealed class RectangleSequenceWriter : SequenceWriterTemplate<RectangleSequence, Rectangle>
    {
        public override void WriteValue(AssetStreamWriter writer, Rectangle value)
        {
            writer.Write(value);
        }
    }
}
