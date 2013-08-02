using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Reflection;

namespace Bibim
{
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = false, Inherited = false)]
    public sealed class ClassIDAttribute : Attribute
    {
        #region Properties
        public int ClassID
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public ClassIDAttribute(char a, char b, char c, char d)
            : this(FOURCC.Make(a, b, c, d))
        {
        }

        public ClassIDAttribute(int classID)
        {
            ClassID = classID;
        }
        #endregion

        #region Static Methods
        public static int GetClassID(Type type)
        {
            ClassIDAttribute attribute = type.GetCustomAttribute<ClassIDAttribute>();
            if (attribute != null)
                return attribute.ClassID;
            else
                return 0;
        }
        #endregion
    }
}
