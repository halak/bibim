using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(GameAssetEvalTree))]
    public sealed class GameAssetEvalTreeWriter : EvalTreeWriterTemplate<GameAssetEvalTree, GameAsset>
    {
    }
}
