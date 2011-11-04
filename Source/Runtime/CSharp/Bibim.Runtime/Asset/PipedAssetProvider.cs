using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Asset
{
    [ClassID('P', 'A', 'S', 'P')]
    public sealed class PipedAssetProvider : AssetProvider
    {
        #region Constants
        public static readonly string DefaultPipeName = "BibimAssetPipe";
        public const uint LoadAssetPacketID = 1000;
        public const uint ChangeClientNamePacketID = 1001;
        public const uint ChangeWorkingDirectoryPacketID = 1002;
        #endregion

        public override GameAsset Load(string name)
        {
            throw new NotImplementedException();
        }
    }
}
