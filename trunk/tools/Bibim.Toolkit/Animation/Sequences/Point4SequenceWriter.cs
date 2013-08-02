using System;
using Bibim.Asset;
using Bibim.IO;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(Point4Sequence))]
    public sealed class Point4SequenceWriter : SequenceWriterTemplate<Point4Sequence, Point4>
    {
        protected override void WriteValue(AssetStreamWriter writer, Point4 value)
        {
            writer.Write(value);
        }
    }
}
