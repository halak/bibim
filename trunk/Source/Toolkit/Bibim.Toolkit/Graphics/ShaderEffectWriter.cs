using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Bibim.Asset;

namespace Bibim.Graphics
{
    [GameAssetWriter(typeof(ShaderEffect))]
    public sealed class ShaderEffectWriter : GameAssetWriter<ShaderEffect>
    {
        public override void Write(AssetStreamWriter writer, ShaderEffect asset)
        {
            writer.Write(asset.ClassID);
            writer.Write(asset.GraphicsDevice);

            var tag = (ShaderEffectCookingTag)asset.Tag;
            writer.Write(tag.Buffer.Length);
            writer.Write(tag.Buffer);
        }
    }
}
