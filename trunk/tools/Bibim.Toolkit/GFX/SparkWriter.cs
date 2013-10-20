using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.Asset.Pipeline;
using Bibim.IO;

namespace Bibim.GFX
{
    [GameAssetWriter(typeof(Spark))]
    public sealed class SparkWriter : GameAssetWriter<Spark>
    {
        public override void Write(AssetStreamWriter writer, Spark asset)
        {
            writer.Write(asset.ClassID);
            WriteBody(writer, asset);
        }

        public static void WriteBody(AssetStreamWriter writer, Spark asset)
        {
            writer.WriteBibimString(asset.Descriptor);
        }
    }
}
