using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Halak.Bibim.Asset;

namespace Halak.Bibim.Graphics
{
    [GameAssetWriter(typeof(CookingSourceTexture2D))]
    public sealed class CookingSourceTexture2DWriter : GameAssetWriter<CookingSourceTexture2D>
    {
        public override void Write(AssetStreamWriter writer, CookingSourceTexture2D asset)
        {
            writer.Write(asset.Texture.ClassID);
            writer.Write(asset.Texture.GraphicsDevice);
            writer.Write((short)asset.Texture.Width);
            writer.Write((short)asset.Texture.Height);
            writer.Write((short)asset.Texture.SurfaceWidth);
            writer.Write((short)asset.Texture.SurfaceHeight);
            writer.Write(asset.Pitch);
            writer.Write(asset.Buffer);
        }
    }
}
