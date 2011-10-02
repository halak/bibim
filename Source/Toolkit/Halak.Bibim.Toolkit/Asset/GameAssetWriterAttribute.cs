using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim.Asset
{
    [AttributeUsage(AttributeTargets.Class)]
    public sealed class GameAssetWriterAttribute : Attribute
    {
        #region Properties
        public Type AssetType
        {
            get;
            private set;
        }
        #endregion

        #region Constructor
        public GameAssetWriterAttribute(Type assetType)
        {
            AssetType = assetType;
        }
        #endregion
    }
}
