using System;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(Point3Sequence))]
    public sealed class Point3SequenceWriter : SequenceWriterTemplate<Point3Sequence, Point3>
    {
        protected override void WriteValue(AssetStreamWriter writer, Point3 value)
        {
            writer.Write(value);
        }
    }
}
