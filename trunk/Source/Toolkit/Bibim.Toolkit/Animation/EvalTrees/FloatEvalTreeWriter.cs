using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(FloatEvalTree))]
    public sealed class FloatEvalTreeWriter : EvalTreeWriterTemplate<FloatEvalTree, float>
    {
    }
}
