using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;

namespace Bibim.Graphics
{
    [GameAssetWriter(typeof(SourceTexture2D))]
    public sealed class SourceTexture2DWriter : GameAssetWriter<SourceTexture2D>
    {
        public override void Write(AssetStreamWriter writer, SourceTexture2D asset)
        {
            writer.Write(asset.ClassID);
            writer.Write(asset.GraphicsDevice);
            writer.Write((short)asset.Width);
            writer.Write((short)asset.Height);
            writer.Write((short)asset.SurfaceWidth);
            writer.Write((short)asset.SurfaceHeight);
            writer.Write((byte)asset.Format);

            var tag = (SourceTexture2DCookingTag)asset.Tag;
            writer.Write(tag.Pitch);
            writer.Write(tag.Buffer);
        }
    }
}
