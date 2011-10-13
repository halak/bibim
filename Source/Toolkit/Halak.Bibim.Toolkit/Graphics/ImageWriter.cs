using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Halak.Bibim.Asset;
using Halak.Bibim.Asset.Pipeline;

namespace Halak.Bibim.Graphics
{
    [GameAssetWriter(typeof(Image))]
    public sealed class ImageWriter : GameAssetWriter<Image>
    {
        public override void Write(AssetStreamWriter writer, Image asset)
        {
        }
    }
}
