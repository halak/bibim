using System;
using Bibim.Asset;

namespace Bibim.Animation
{
    [ClassID('e', 'r', 'a', '_')]
    public sealed class EvalGameAssetRangedSequence : EvalRangedSequenceTemplate<GameAsset, GameAssetSequence>
    {
        protected override GameAsset Interpolate(GameAsset a, GameAsset b, float t)
        {
            return a;
        }
    }
}