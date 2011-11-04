using System;
using Bibim.Asset;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'a', '_')]
    public sealed class EvaluableGameAssetVariable : EvaluableVariableTemplate<GameAsset>
    {
        #region Constructors
        public EvaluableGameAssetVariable()
        {
        }

        public EvaluableGameAssetVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
