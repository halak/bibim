using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;

namespace Halak.Bibim.Reflection
{
    public static class TypeExtension
    {
        #region Methods
        public static ConstructorInfo GetConstructor(this Type type)
        {
            return type.GetConstructor(AssemblyUtility.EmptyTypes);
        }

        public static object GetCustomAttribute(this Type type, Type attributeType)
        {
            return GetCustomAttribute(type, attributeType, false);
        }

        public static object GetCustomAttribute(this Type type, Type attributeType, bool inherit)
        {
            object[] customAttributes = type.GetCustomAttributes(attributeType, inherit);
            if (customAttributes.Length > 0)
                return customAttributes[0];
            else
                return null;
        }

        public static T GetCustomAttribute<T>(this Type type) where T : Attribute
        {
            return GetCustomAttribute<T>(type, false);
        }

        public static T GetCustomAttribute<T>(this Type type, bool inherit) where T : Attribute
        {
            object[] customAttributes = type.GetCustomAttributes(typeof(T), inherit);
            if (customAttributes.Length > 0)
                return (T)customAttributes[0];
            else
                return null;
        }
        #endregion
    }
}
