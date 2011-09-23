using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;

namespace Halak.Bibim.Reflection
{
    public static class AssemblyUtility
    {
        public static ICollection<Type> FindClasses(Type baseClass)
        {
            return FindClasses(baseClass, false, false);
        }

        public static ICollection<Type> FindClasses(Type baseClass, bool creatableOnly, bool emptyConstructorOnly)
        {
            List<Type> result = new List<Type>();
            Type[] emptyTypes = emptyConstructorOnly ? new Type[0] : null;

            foreach (Assembly assembly in AppDomain.CurrentDomain.GetAssemblies())
            {
                foreach (Type item in assembly.GetTypes())
                {
                    if (creatableOnly && item.IsAbstract)
                        continue;

                    if (item.IsClass &&
                        item.IsPublic &&
                        item.IsSubclassOf(baseClass))
                    {
                        if (emptyConstructorOnly &&
                            item.GetConstructor(emptyTypes) == null)
                            continue;

                        result.Add(item);
                    }
                }
            }

            return result;
        }
    }
}
