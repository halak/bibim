using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Asset
{
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = false, Inherited = false)]
    public class GameAssetAttribute : Attribute
    {
        #region Properties
        public uint ClassID
        {
            get;
            private set;
        }

        public Type ReaderType
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public GameAssetAttribute(char a, char b, char c, char d)
            : this(FOURCC.Make(a, b, c, d), null)
        {
        }

        public GameAssetAttribute(char a, char b, char c, char d, Type readerType)
            : this(FOURCC.Make(a, b, c, d), readerType)
        {
        }

        public delegate void ReadFunc();

        public GameAssetAttribute( ReadFunc readFunc)
            : this(0, null)
        {
        }

        public GameAssetAttribute(uint classID, Type readerType)
        {
            ClassID = classID;
            ReaderType = readerType;
        }
        #endregion

        #region StaticMethods
        public static uint GetClassID(Type type)
        {
            object[] attributes = type.GetCustomAttributes(typeof(GameModuleAttribute), false);
            if (attributes != null && attributes.Length > 0)
                return ((GameModuleAttribute)attributes[0]).ClassID;
            else
                return 0;
        }
        #endregion
    }
}
