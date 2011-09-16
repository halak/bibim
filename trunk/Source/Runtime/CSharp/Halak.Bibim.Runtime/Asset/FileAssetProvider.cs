using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Asset
{
    [GameModule('F', 'A', 'S', 'P')]
    public sealed class FileAssetProvider : AssetProvider
    {
        public override GameAsset Load(string name)
        {
            throw new NotImplementedException();
        }
    }
}
