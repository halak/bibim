using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.Asset.Pipeline;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(Sprite))]
    public sealed class SpriteWriter : GameAssetWriter<Sprite>
    {
        public override void Write(AssetStreamWriter writer, Sprite asset)
        {
            writer.Write(asset.ClassID);
            WriteBody(writer, asset);
        }

        public static void WriteBody(AssetStreamWriter writer, Sprite asset)
        {
            writer.Write((byte)asset.BlendMode);
            writer.Write((short)asset.Keyframes.Length);
            foreach (var item in asset.Keyframes)
            {
                writer.WriteBibimString(item.TextureURI);
                writer.Write(item.ClippingRectangle);
                writer.Write((byte)item.AppliedTransform);
                writer.Write(item.Origin);
                writer.Write(item.Duration);
            }
        }
    }
}
