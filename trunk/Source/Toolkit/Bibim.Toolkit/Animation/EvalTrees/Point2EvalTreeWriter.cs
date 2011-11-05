using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(Point2EvalTree))]
    public sealed class Point2EvalTreeWriter : EvalTreeWriterTemplate<Point2EvalTree, Point2>
    {
        public override void WriteValue(AssetStreamWriter writer, Point2 value)
        {
            writer.Write(value);
        }
    }
}
