using System;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(GameAssetSequence))]
    public sealed class GameAssetSequenceWriter : SequenceWriterTemplate<GameAssetSequence, GameAsset>
    {
        public override void WriteValue(AssetStreamWriter writer, GameAsset value)
        {
            writer.Write(value);
        }
    }
}
