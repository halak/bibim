using System;
using Bibim.Asset;
using Bibim.IO;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(PointSequence))]
    public sealed class PointSequenceWriter : SequenceWriterTemplate<PointSequence, Point>
    {
        public override void WriteValue(AssetStreamWriter writer, Point value)
        {
            writer.Write(value);
        }
    }
}
