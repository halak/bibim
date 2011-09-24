﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Asset
{
    [GameModule('A', 'S', 'P', 'V')]
    public abstract class AssetProvider : GameModule
    {
        #region Constants
        public const uint LoadAssetPacketID = 1000;
        public const uint PreloadAssets = 1001;
        public const uint PreloadAssetsFromDirectory = 1002;
        #endregion

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
