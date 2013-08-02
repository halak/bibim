using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using Bibim.IO;

namespace Bibim.Asset
{
    public sealed class AssetStreamWriter : BinaryWriter
    {
        #region Properties
        public GameModuleTree Modules
        {
            get;
            private set;
        }

        public GameAssetStorage Storage
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public AssetStreamWriter()
        {
        }

        public AssetStreamWriter(Stream output, GameModuleTree modules)
            : this(output, modules, null)
        {
        }

        public AssetStreamWriter(Stream output, GameModuleTree modules, GameAssetStorage storage)
            : base(output)
        {
            Modules = modules;
            Storage = storage ?? (GameAssetStorage)modules.Root.FindChildByClassID(ClassIDAttribute.GetClassID(typeof(GameAssetStorage)));
        }
        #endregion

        #region Methods
        public void Write(GameModule module)
        {
            if (module != null && module.ID != GameModule.UnspecifiedID)
                Write(module.ID);
            else
                Write((uint)0);
        }

        public void Write(GameAsset asset)
        {
            string name = Storage.FindName(asset);
            if (string.IsNullOrEmpty(name) == false)
                this.WriteBibimString(name);
            else
                this.WriteBibimString(string.Empty);
        }
        #endregion
    }
}
