using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Toolkit.Workbench.Consoles
{
    public abstract class ConsoleProgram
    {
        #region Constructors
        protected ConsoleProgram()
        {
        }
        #endregion

        #region Methods
        public abstract void Run();
        #endregion
    }
}
