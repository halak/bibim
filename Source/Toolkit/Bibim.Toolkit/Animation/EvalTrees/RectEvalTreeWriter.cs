using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(RectEvalTree))]
    public sealed class RectEvalTreeWriter : EvalTreeWriterTemplate<RectEvalTree, Rectangle>
    {
    }
}
