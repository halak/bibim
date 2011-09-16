using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Asset
{
    public abstract class GameAsset
    {
        #region Properties
        public uint ClassID
        {
            get { return GameAssetAttribute.GetClassID(GetType()); }
        }
        #endregion
    }
}
