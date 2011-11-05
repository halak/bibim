using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;

namespace Bibim.Animation
{
    [ClassID('e', 't', 'a', '_')]
    public sealed class GameAssetEvalTree : EvalTreeTemplate<GameAsset>
    {
        #region Constructors
        public GameAssetEvalTree()
        {
        }

        public GameAssetEvalTree(Eval<GameAsset> root)
            : base(root)
        {
        }
        #endregion
    }
}
