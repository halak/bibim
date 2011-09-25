using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Halak.Bibim.Reflection;

namespace Halak.Bibim.UI
{
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = false, Inherited = false)]
    public sealed class UIElementAttribute : Attribute
    {
        #region Properties
        public uint ClassID
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public UIElementAttribute(char a, char b, char c, char d)
            : this(FOURCC.Make(a, b, c, d))
        {
        }

        public UIElementAttribute(uint classID)
        {
            ClassID = classID;
        }
        #endregion

        #region Static Methods
        public static uint GetClassID(Type type)
        {
            UIElementAttribute attribute = type.GetCustomAttribute<UIElementAttribute>();
            if (attribute != null)
                return attribute.ClassID;
            else
                return 0;
        }
        #endregion
    }
}
