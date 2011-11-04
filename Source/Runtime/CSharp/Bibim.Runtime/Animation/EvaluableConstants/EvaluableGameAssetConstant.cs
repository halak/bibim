using System;
using Bibim.Asset;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'a', '_')]
    public sealed class EvaluableGameAssetConstant : EvaluableConstantTemplate<GameAsset>
    {
        #region Constructors
        public EvaluableGameAssetConstant()
        {
        }

        public EvaluableGameAssetConstant(GameAsset value)
            : base(value)
        {
        }
        #endregion
    }
}
