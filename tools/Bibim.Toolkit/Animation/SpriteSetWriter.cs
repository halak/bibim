using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.Asset.Pipeline;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(SpriteSet))]
    public sealed class SpriteSetWriter : GameAssetWriter<SpriteSet>
    {
        public override void Write(AssetStreamWriter writer, SpriteSet asset)
        {
            writer.Write(asset.ClassID);
            writer.Write((short)asset.Sprites.Count);
            foreach (var item in asset.Sprites)
            {
                writer.WriteBibimString(item.Key);
                SpriteWriter.WriteBody(writer, item.Value);
            }
        }
    }
}
