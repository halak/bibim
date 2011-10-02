using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim.Asset
{
    [ClassID('A', 'S', 'P', 'V')]
    public abstract class AssetProvider : GameModule
    {
        #region Fields
        private GameAssetStorage storage;
        #endregion

        #region Properties
        public GameAssetStorage Storage
        {
            get { return storage; }
            set
            {
                if (storage != value)
                {
                    if (storage != null)
                        storage.Remove(this);

                    storage = value;

                    if (storage != null)
                        storage.Add(this);
                }
            }
        }
        #endregion

        #region Constructors
        protected AssetProvider()
        {
        }
        #endregion

        #region Methods
        public abstract GameAsset Load(string name);
        #endregion
    }
}
