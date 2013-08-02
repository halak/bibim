using System;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(Point2Sequence))]
    public sealed class Point2SequenceWriter : SequenceWriterTemplate<Point2Sequence, Point2>
    {
        protected override void WriteValue(AssetStreamWriter writer, Point2 value)
        {
            writer.Write(value);
        }
    }
}
