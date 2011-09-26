using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Halak.Bibim.Asset;

namespace Halak.Bibim.UI
{
    [GameAssetWriter(typeof(UILayout))]
    public sealed class UILayoutWriter : GameAssetWriter<UILayout>
    {
        public override void Write(AssetStreamWriter writer, UILayout asset)
        {
        }
    }
}
