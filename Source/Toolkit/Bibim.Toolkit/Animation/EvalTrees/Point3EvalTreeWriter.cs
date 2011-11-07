using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(Point3EvalTree))]
    public sealed class Point3EvalTreeWriter : EvalTreeWriterTemplate<Point3EvalTree, Point3>
    {
    }
}
