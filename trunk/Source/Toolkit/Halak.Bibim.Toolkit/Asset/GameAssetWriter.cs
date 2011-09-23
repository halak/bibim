using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Halak.Bibim.Reflection;

namespace Halak.Bibim.Asset
{
    public abstract class GameAssetWriter
    {
        #region Static Field
        private static readonly object[] emptyObjects;
        private static readonly Dictionary<Type, Type> writerClasses;
        #endregion

        #region Constructor
        protected GameAssetWriter()
        {
        }
        #endregion

        #region Static Constructor
        static GameAssetWriter()
        {
            emptyObjects = new object[0];
            writerClasses = new Dictionary<Type, Type>();
            foreach (Type item in AssemblyUtility.FindClasses(typeof(GameAssetWriter), true, true))
            {
                GameAssetWriterAttribute attribute = item.GetCustomAttribute<GameAssetWriterAttribute>();
                writerClasses.Add(attribute.AssetType, item);
            }
        }
        #endregion

        #region Method
        public abstract void Write(AssetStreamWriter writer, object asset);
        #endregion

        #region Static Method
        public static GameAssetWriter CreateWriter(Type assetType)
        {
            Type type = null;
            if (writerClasses.TryGetValue(assetType, out type))
                return (GameAssetWriter)type.GetConstructor().Invoke(emptyObjects);
            else
                return null;
        }
        #endregion
    }

    public abstract class GameAssetWriter<T> : GameAssetWriter
    {
        #region Constructor
        protected GameAssetWriter()
        {
        }
        #endregion

        #region Methods
        public abstract void Write(AssetStreamWriter writer, T asset);

        public override void Write(AssetStreamWriter writer, object asset)
        {
            this.Write(writer, (T)asset);
        }
        #endregion
    }
}
