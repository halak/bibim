using System;
using System.Collections.Generic;
using System.Runtime.Serialization;
using System.Text;

namespace Bibim.Asset
{
    public abstract class GameAsset
    {
        #region Fields
        public static readonly string TextFileExtension = "asset";
        public static readonly string BinaryFileExtension = "ab";
        #endregion

        #region Properties
        public int ClassID
        {
            get { return ClassIDAttribute.GetClassID(GetType()); }
        }
        
        public GameAssetStatus Status
        {
            get;
            protected set;
        }

        public uint Revision
        {
            get;
            protected set;
        }

        public object Tag
        {
            get;
            set;
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
