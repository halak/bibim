using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Halak.Bibim.Asset;

namespace Halak.Bibim.Typography
{
    [GameAssetWriter(typeof(Font))]
    public sealed class FontWriter : GameAssetWriter<Font>
    {
        public override void Write(AssetStreamWriter writer, Font asset)
        {
        }
    }
}
