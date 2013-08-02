using System;
using Bibim.Asset;

namespace Bibim.Animation
{
    [ClassID('e', 'v', 'a', '_')]
    public sealed class EvalGameAssetVariable : EvalVariableTemplate<GameAsset>
    {
        #region Constructors
        public EvalGameAssetVariable()
        {
        }

        public EvalGameAssetVariable(string name)
            : base(name)
        {
        }
        #endregion
    }
}
