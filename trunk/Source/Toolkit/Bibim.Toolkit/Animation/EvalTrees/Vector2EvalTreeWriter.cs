using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;
using Microsoft.Xna.Framework;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(Vector2EvalTree))]
    public sealed class Vector2EvalTreeWriter : EvalTreeWriterTemplate<Vector2EvalTree, Vector2>
    {
    }
}
