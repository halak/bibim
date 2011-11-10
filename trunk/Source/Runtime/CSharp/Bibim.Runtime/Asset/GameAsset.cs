using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Serialization;

namespace Bibim.Asset
{
    public abstract class GameAsset
    {
        #region Fields
        public static readonly string TextFileExtension = "asset";
        public static readonly string BinaryFileExtension = "ab";
        #endregion

        #region Properties
        [XmlIgnore]
        public int ClassID
        {
            get { return ClassIDAttribute.GetClassID(GetType()); }
        }
        
        [XmlIgnore]
        public GameAssetStatus Status
        {
            get;
            protected set;
        }

        [XmlIgnore]
        public uint Revision
        {
            get;
            protected set;
        }

        [XmlIgnore]
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
