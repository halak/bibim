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

        public GameAssetStatus Status
        {
            get;
            protected set;
        }

        public uint Revision
        {
            get;
            private set;
        }
        #endregion

        #region Constructor
        protected GameAsset()
        {
            Status = GameAssetStatus.Empty;
            Revision = 0;
        }
        #endregion
    }
}
