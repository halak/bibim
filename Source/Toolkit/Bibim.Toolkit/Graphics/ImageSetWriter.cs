using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.Asset.Pipeline;
using Bibim.IO;

namespace Bibim.Graphics
{
    [GameAssetWriter(typeof(ImageSet))]
    public sealed class ImageSetWriter : GameAssetWriter<ImageSet>
    {
        public override void Write(AssetStreamWriter writer, ImageSet asset)
        {
            writer.Write(asset.ClassID);
            writer.Write((short)asset.Images.Count);
            foreach (var item in asset.Images)
            {
                writer.WriteBibimString(item.Key);
                ImageWriter.WriteBody(writer, item.Value);
            }
        }
    }
}
