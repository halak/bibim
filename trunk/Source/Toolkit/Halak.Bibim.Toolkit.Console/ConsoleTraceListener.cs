using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using C = System.Console;

namespace Halak.Bibim.Toolkit.Console
{
    public sealed class ConsoleTraceListener : TraceListener
    {
        #region Static Properties
        public static ConsoleTraceListener Instance
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        private ConsoleTraceListener()
        {
        }

        static ConsoleTraceListener()
        {
            Instance = new ConsoleTraceListener();
        }
        #endregion

        #region Methods
        public override void Write(string message)
        {
            C.Write(message);
        }

        public override void WriteLine(string message)
        {
            C.WriteLine(message);
        }
        #endregion
    }
}
