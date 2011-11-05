using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(RectFEvalTree))]
    public sealed class RectFEvalTreeWriter : EvalTreeWriterTemplate<RectFEvalTree, RectangleF>
    {
        public override void WriteValue(AssetStreamWriter writer, RectangleF value)
        {
            writer.Write(value);
        }
    }
}
