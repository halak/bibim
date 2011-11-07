using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(LongIntEvalTree))]
    public sealed class LongIntEvalTreeWriter : EvalTreeWriterTemplate<LongIntEvalTree, long>
    {
    }
}
