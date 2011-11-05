using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(ShortIntEvalTree))]
    public sealed class ShortIntEvalTreeWriter : EvalTreeWriterTemplate<ShortIntEvalTree, short>
    {
        public override void WriteValue(AssetStreamWriter writer, short value)
        {
            writer.Write(value);
        }
    }
}
