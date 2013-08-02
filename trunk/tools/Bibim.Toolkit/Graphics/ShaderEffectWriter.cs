using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;

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
            writer.Write(tag.Extra);
            writer.Write(tag.Code.Length);
            writer.Write(tag.Code);
        }
    }
}
