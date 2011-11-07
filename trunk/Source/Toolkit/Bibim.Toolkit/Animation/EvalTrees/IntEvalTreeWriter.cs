using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(IntEvalTree))]
    public sealed class IntEvalTreeWriter : EvalTreeWriterTemplate<IntEvalTree, int>
    {
    }
}
