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
        #region Fields
        private object consoleLock = new object();
        #endregion

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
            ConsoleColor color = ConsoleColor.Black;
            if (GetHighlightColor(message, ref color))
            {
                lock (consoleLock)
                {
                    ConsoleColor old = C.ForegroundColor;
                    C.ForegroundColor = color;
                    C.Write(message);
                    C.ForegroundColor = old;
                }
            }
            else
                C.Write(message);
        }

        public override void WriteLine(string message)
        {
            ConsoleColor color = ConsoleColor.Black;
            if (GetHighlightColor(message, ref color))
            {
                lock (consoleLock)
                {
                    ConsoleColor old = C.ForegroundColor;
                    C.ForegroundColor = color;
                    C.WriteLine(message);
                    C.ForegroundColor = old;
                }
            }
            else
                C.WriteLine(message);
        }

        private bool GetHighlightColor(string message, ref ConsoleColor color)
        {
            if (message.StartsWith("!!"))
            {
                color = ConsoleColor.Red;
                return true;
            }
            else if (message.StartsWith("!"))
            {
                color = ConsoleColor.Yellow;
                return true;
            }
            else if (message.StartsWith("#"))
            {
                color = ConsoleColor.Green;
                return true;
            }
            else
                return false;
        }
        #endregion
    }
}
