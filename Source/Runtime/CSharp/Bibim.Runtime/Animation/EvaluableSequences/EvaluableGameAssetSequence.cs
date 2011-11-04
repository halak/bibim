using System;
using Bibim.Asset;

namespace Bibim.Animation
{
    [ClassID('e', 's', 'a', '_')]
    public sealed class EvaluableGameAssetSequence : EvaluableSequenceTemplate<GameAsset, GameAssetSequence>
    {
        protected override GameAsset Interpolate(GameAsset a, GameAsset b, float t)
        {
            return a;
        }
    }
}