using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;

namespace Halak.Bibim.Asset
{
    public sealed class AssetStreamWriter : BinaryWriter
    {
        #region Properties
        public GameModuleTree Modules
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
            : base(output)
        {
            Modules = modules;
        }
        #endregion

        #region Methods
        public void Write(GameModule module)
        {
            if (module != null)
                Write(module.ID);
            else
                Write((uint)0);
        }
        #endregion
    }
}
