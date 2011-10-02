using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim.Asset
{
    public abstract class GameAssetReader
    {
        #region Constructor
        protected GameAssetReader()
        {
        }
        #endregion

        public abstract GameAsset Read(AssetStreamReader reader, GameAsset existingInstance);
    }

    public abstract class GameAssetReader<T> : GameAssetReader where T : GameAsset
    {
        #region Constructor
        protected GameAssetReader()
        {
        }
        #endregion

        #region Methods
        public override GameAsset Read(AssetStreamReader reader, GameAsset existingInstance)
        {
            throw new NotImplementedException();
        }

        public abstract T Read(AssetStreamReader reader, T existingInstance);
        #endregion
    }
}
