using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Scripting.Libraries
{
    [ScriptNativeLibrary]
    public static class IO
    {
        [ScriptNativeFunction('p', 'r', 'n', 't')]
        [ScriptNativeFunctionParameter(ScriptObjectType.String)]
        public static void Print(ScriptingContext context)
        {
        }
    }
}
