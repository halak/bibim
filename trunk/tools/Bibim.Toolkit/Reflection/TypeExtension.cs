using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;

namespace Bibim.Reflection
{
    public static class TypeExtension
    {
        #region Methods
        public static ConstructorInfo GetConstructor(this Type type)
        {
            return type.GetConstructor(AssemblyUtility.EmptyTypes);
        }
        #endregion
    }
}
