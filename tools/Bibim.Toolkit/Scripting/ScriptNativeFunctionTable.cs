using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Reflection;
using Bibim.Reflection;

namespace Bibim.Scripting
{
    public static class ScriptNativeFunctionTable
    {
        #region Fields
        private static Dictionary<string, ScriptNativeFunction> functions;
        #endregion
        
        #region Methods
        public static void Rebuild()
        {
            functions = functions ?? new Dictionary<string, ScriptNativeFunction>();
            functions.Clear();

            foreach (Assembly assembly in AppDomain.CurrentDomain.GetAssemblies())
            {
                try
                {
                    foreach (Type item in assembly.GetExportedTypes())
                    {
                        if (item.IsDefined(typeof(ScriptNativeLibraryAttribute), false) == false)
                            continue;

                        foreach (MethodInfo method in item.GetMethods())
                        {
                            if (method.IsDefined(typeof(ScriptNativeFunctionAttribute), false) == false)
                                continue;

                            Debug.Assert(method.IsStatic);
                            Debug.Assert(method.ReturnType == typeof(void));
                            Debug.Assert(method.GetParameters().Length == 1);
                            Debug.Assert(method.GetParameters()[0].ParameterType == typeof(ScriptingContext));

                            functions.Add(method.Name, (ScriptNativeFunction)Delegate.CreateDelegate(typeof(ScriptNativeFunction), method));
                        }
                    }
                }
                catch (Exception)
                {
                }
            }
        }

        public static ScriptNativeFunction Find(string name)
        {
            if (functions == null)
                Rebuild();

            ScriptNativeFunction result;
            if (functions.TryGetValue(name, out result))
                return result;
            else
                return null;
        }
        #endregion
    }
}
