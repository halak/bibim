using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Asset
{
    [ClassID('P', 'A', 'S', 'P')]
    public sealed class NetworkAssetProvider : AssetProvider
    {
        public static int DefaultPort = 51894;
        
        public override GameAsset Load(string name)
        {
            throw new NotImplementedException();
        }
    }
}
