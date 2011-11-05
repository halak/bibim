using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(BoolEvalTree))]
    public sealed class BoolEvalTreeWriter : EvalTreeWriterTemplate<BoolEvalTree, bool>
    {
        public override void WriteValue(AssetStreamWriter writer, bool value)
        {
            writer.Write(value);
        }
    }
}
