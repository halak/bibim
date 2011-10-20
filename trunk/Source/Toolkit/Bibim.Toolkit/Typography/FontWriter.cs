using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;
using Microsoft.Xna.Framework;

namespace Bibim.Typography
{
    [GameAssetWriter(typeof(Font))]
    public sealed class FontWriter : GameAssetWriter<Font>
    {
        public override void Write(AssetStreamWriter writer, Font asset)
        {
            writer.Write(asset.ClassID);
            writer.Write(asset.Library);
            writer.WriteBibimString(asset.FaceURI);
            writer.Write(asset.FontSize);
            writer.Write(asset.StrokeSize);
            writer.Write(asset.Weights);
            writer.Write(asset.Shear);
            writer.Write(asset.GlowSize);
            writer.Write(asset.GlowSpread);
            writer.Write(asset.GlowThickness);
            writer.Write(asset.Scale);
            writer.Write(asset.Hinting);
            writer.Write(asset.IgnoreBitmap);
            writer.Write(asset.Spacing);
            writer.Write(asset.Color);
            writer.Write(asset.StrokeColor);
            writer.Write(asset.GlowColor);
        }
    }
}
