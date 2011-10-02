using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

namespace Halak.Bibim.Asset
{
    [ClassID('G', 'A', 'S', 'T')]
    public class GameAssetStorage : GameModule
    {
        #region Fields
        private Dictionary<string, GameAsset> assets;
        private List<AssetProvider> providers;
        #endregion

        #region Properties
        public IEnumerable<KeyValuePair<string, GameAsset>> Assets
        {
            get { return assets; }
        }

        public IEnumerable<AssetProvider> Providers
        {
            get { return providers; }
        }
        #endregion

        #region Constructors
        public GameAssetStorage()
        {
            assets = new Dictionary<string, GameAsset>();
            providers = new List<AssetProvider>();
        }
        #endregion

        #region Methods
        public GameAsset Load(string name)
        {
            GameAsset result = null;
            if (assets.TryGetValue(name, out result))
                return result;
            else
            {
                foreach (AssetProvider item in providers)
                {
                    result = item.Load(name);
                    if (result != null)
                        return result;
                }

                return null;
            }
        }

        /// <summary>
        /// call in AssetProvider
        /// </summary>
        /// <param name="item"></param>
        internal void Add(AssetProvider item)
        {
            Debug.Assert(providers.Contains(item) == false);

            providers.Add(item);
        }

        /// <summary>
        /// call in AssetProvider
        /// </summary>
        /// <param name="item"></param>
        internal void Remove(AssetProvider item)
        {
            providers.Remove(item);
        }
        #endregion
    }
}
