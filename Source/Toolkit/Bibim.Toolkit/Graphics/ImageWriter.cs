using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.Asset.Pipeline;
using Bibim.IO;

namespace Bibim.Graphics
{
    [GameAssetWriter(typeof(Image))]
    public sealed class ImageWriter : GameAssetWriter<Image>
    {
        public override void Write(AssetStreamWriter writer, Image asset)
        {
            writer.Write(asset.ClassID);
            WriteBody(writer, asset);
        }

        public static void WriteBody(AssetStreamWriter writer, Image asset)
        {
            writer.WriteURI(asset.TextureURI);
            writer.Write(asset.ClippingRectangle);
            writer.Write((byte)asset.AppliedTransform);
        }
    }
}
