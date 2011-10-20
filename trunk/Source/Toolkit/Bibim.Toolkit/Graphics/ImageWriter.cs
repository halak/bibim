using System;
using System.Collections.Generic;
using System.Linq;
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
            writer.WriteBibimString(asset.TextureURI);
            writer.Write(asset.ClippingRectangle);
            writer.Write((byte)asset.AppliedTransform);
        }
    }
}
