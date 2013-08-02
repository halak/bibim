using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text;

namespace Bibim.Reflection
{
    public static class MemberInfoExtension
    {
        #region Methods
        public static object GetCustomAttribute(this MemberInfo member, Type attributeType)
        {
            return GetCustomAttribute(member, attributeType, false);
        }

        public static object GetCustomAttribute(this MemberInfo member, Type attributeType, bool inherit)
        {
            object[] customAttributes = member.GetCustomAttributes(attributeType, inherit);
            if (customAttributes.Length > 0)
                return customAttributes[0];
            else
                return null;
        }

        public static T GetCustomAttribute<T>(this MemberInfo member) where T : Attribute
        {
            return GetCustomAttribute<T>(member, false);
        }

        public static T GetCustomAttribute<T>(this MemberInfo member, bool inherit) where T : Attribute
        {
            object[] customAttributes = member.GetCustomAttributes(typeof(T), inherit);
            if (customAttributes.Length > 0)
                return (T)customAttributes[0];
            else
                return null;
        }

        public static T[] GetCustomAttributes<T>(this MemberInfo member) where T : Attribute
        {
            return GetCustomAttributes<T>(member, false);
        }

        public static T[] GetCustomAttributes<T>(this MemberInfo member, bool inherit) where T : Attribute
        {
            object[] customAttributes = member.GetCustomAttributes(typeof(T), inherit);
            if (customAttributes.Length > 0)
            {
                T[] result = new T[customAttributes.Length];
                for (int i = 0; i < result.Length; i++)
                    result[i] = (T)customAttributes[i];

                return result;
            }
            else
                return new T[] { };
        }
        #endregion
    }
}
