using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(Point4EvalTree))]
    public sealed class Point4EvalTreeWriter : EvalTreeWriterTemplate<Point4EvalTree, Point4>
    {
    }
}
