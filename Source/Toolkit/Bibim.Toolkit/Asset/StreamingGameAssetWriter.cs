using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Asset
{
    [GameAssetWriter(typeof(StreamingGameAsset))]
    public sealed class StreamingGameAssetWriter : GameAssetWriter<StreamingGameAsset>
    {
        public override void Write(AssetStreamWriter writer, StreamingGameAsset asset)
        {
            writer.Write(asset.Data.Length);
            writer.Write(asset.Data);
        }
    }
}
