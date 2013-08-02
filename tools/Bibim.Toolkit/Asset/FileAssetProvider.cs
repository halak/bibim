using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Asset
{
    [ClassID('F', 'A', 'S', 'P')]
    public sealed class FileAssetProvider : AssetProvider
    {
        public override GameAsset Load(string name)
        {
            throw new NotImplementedException();
        }
    }
}
