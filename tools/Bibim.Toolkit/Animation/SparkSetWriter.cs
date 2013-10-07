using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.Asset.Pipeline;
using Bibim.IO;
using Bibim.Graphics;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(SparkSet))]
    public sealed class SparkSetWriter : GameAssetWriter<SparkSet>
    {
        public override void Write(AssetStreamWriter writer, SparkSet asset)
        {
            writer.Write(asset.ClassID);
            ImageSetWriter.WriteBody(writer, asset.Images);
            writer.Write((short)asset.Sparks.Count);
            foreach (var item in asset.Sparks)
            {
                writer.WriteBibimString(item.Key);
                SparkWriter.WriteBody(writer, item.Value);
            }
        }
    }
}
