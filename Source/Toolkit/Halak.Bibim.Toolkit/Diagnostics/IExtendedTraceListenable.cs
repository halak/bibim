using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Diagnostics
{
    public interface IExtendedTraceListenable
    {
        void TraceObject(object key, string message, object obj);
    }
}
