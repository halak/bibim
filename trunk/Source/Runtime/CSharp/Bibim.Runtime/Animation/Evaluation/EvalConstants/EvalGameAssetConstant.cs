using System;
using Bibim.Asset;

namespace Bibim.Animation
{
    [ClassID('e', 'c', 'a', '_')]
    public sealed class EvalGameAssetConstant : EvalConstantTemplate<GameAsset>
    {
        #region Constructors
        public EvalGameAssetConstant()
        {
        }

        public EvalGameAssetConstant(GameAsset value)
            : base(value)
        {
        }
        #endregion
    }
}
