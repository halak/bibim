using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Asset
{
    public abstract class GameAssetWriter
    {
        #region Constructor
        protected GameAssetWriter()
        {
        }
        #endregion

        public abstract void Write(AssetStreamWriter writer, GameAsset asset);
    }

    public abstract class GameAssetWriter<T> : GameAssetWriter where T : GameAsset
    {
        #region Constructor
        protected GameAssetWriter()
        {
        }
        #endregion

        #region Methods
        public abstract void Write(AssetStreamWriter writer, T asset);

        public override void Write(AssetStreamWriter writer, GameAsset asset)
        {
            this.Write(writer, (T)asset);
        }
        #endregion
    }
}
