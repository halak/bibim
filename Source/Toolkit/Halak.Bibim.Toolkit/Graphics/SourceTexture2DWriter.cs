using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Halak.Bibim.Asset;

namespace Halak.Bibim.Graphics
{
    [GameAssetWriter(typeof(SourceTexture2D))]
    public sealed class SourceTexture2DWriter : GameAssetWriter<SourceTexture2D>
    {
        public override void Write(AssetStreamWriter writer, SourceTexture2D asset)
        {
            //writer.Write(null);
            //writer.Write(asset.Width);
            //writer.Write(asset.Height);
            //writer.Write(asset.SurfaceWidth);
            //writer.Write(asset.SurfaceHeight);

            //asset.GraphicsDevice;
            //asset.Width;
            //asset.Height;
            //asset.SurfaceWidth;
            //asset.SurfaceHeight;
        }
    }
}
