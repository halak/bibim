using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace Bibim.Diagnostics
{
    public static class TraceExtension
    {
        [Conditional("TRACE")]
        public static void TraceObject(object key, string message, object obj)
        {
            TraceObjectActually(Trace.Listeners, key, message, obj);
        }

        internal static void TraceObjectActually(TraceListenerCollection listeners, object key, string message, object obj)
        {
            string fullMessage = null;
            foreach (TraceListener item in Trace.Listeners)
            {
                var extendedItem = item as IExtendedTraceListenable;
                if (extendedItem != null)
                    extendedItem.TraceObject(key, message, obj);
                else
                {
                    if (fullMessage == null)
                        fullMessage = string.Format("{0} : {1}", obj.ToString());

                    item.WriteLine(fullMessage);
                }
            }
        }
    }
}
