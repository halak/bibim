using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text;

namespace Halak.Bibim.Toolkit
{
    [AttributeUsage(AttributeTargets.Module |
                    AttributeTargets.Class | AttributeTargets.Struct | AttributeTargets.Interface | AttributeTargets.Enum |
                    AttributeTargets.Field | AttributeTargets.Property | AttributeTargets.Event | AttributeTargets.Method | AttributeTargets.Parameter, AllowMultiple=true, Inherited=true)]
    public sealed class AliasAttribute : Attribute
    {
        #region Properties
        public string[] Names
        {
            get;
            private set;
        }
        #endregion

        #region Constructor
        public AliasAttribute()
        {
            Names = null;
        }

        public AliasAttribute(params string[] name)
        {
            Names = name;
        }
        #endregion

        #region Methods
        public static bool MatchName(MemberInfo memberInfo, string name)
        {
            if (string.IsNullOrEmpty(name))
                return false;
            if (string.Compare(memberInfo.Name, name, true) == 0)
                return true;

            return MatchName(memberInfo.GetCustomAttributes(typeof(AliasAttribute), true), name);
        }

        public static bool MatchName(ParameterInfo parameterInfo, string name)
        {
            if (string.IsNullOrEmpty(name))
                return false;
            if (string.Compare(parameterInfo.Name, name, true) == 0)
                return true;

            return MatchName(parameterInfo.GetCustomAttributes(typeof(AliasAttribute), true), name);
        }

        private static bool MatchName(object[] attributes, string name)
        {
            foreach (AliasAttribute alias in attributes)
            {
                foreach (string item in alias.Names)
                {
                    if (string.Compare(item, name, true) == 0)
                        return true;
                }
            }

            return false;
        }
        #endregion
    }
}
