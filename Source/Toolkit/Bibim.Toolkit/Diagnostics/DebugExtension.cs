using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace Bibim.Diagnostics
{
    public static class DebugExtension
    {
        [Conditional("DEBUG")]
        public static void TraceObject(object key, string message, object obj)
        {
            TraceExtension.TraceObjectActually(Debug.Listeners, key, message, obj);
        }
    }
}
