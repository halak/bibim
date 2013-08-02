using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text;
using Bibim.Reflection;
using Bibim.Toolkit;

namespace Bibim.Bab.Consoles
{
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = false, Inherited = false)]
    public sealed class ConsoleEntryPointAttribute : Attribute
    {
        public static MethodInfo Find(string name)
        {
            Assembly assembly = Assembly.GetEntryAssembly();
            foreach (Type item in assembly.GetExportedTypes())
            {
                if (item.GetCustomAttribute<ConsoleEntryPointAttribute>() == null)
                    continue;

                if (AliasAttribute.MatchName(item, name))
                {
                    MethodInfo result = item.GetMethod("Run", BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Static);
                    if (result != null)
                        return result;
                }
            }

            return null;
        }
    }
}
