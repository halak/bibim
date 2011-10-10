using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim.Scripting.Statements
{
    public abstract class Statement
    {
        #region Constructors
        protected Statement()
        {
        }
        #endregion

        #region Methods
        public abstract void Generate(ScriptCompiler.Context context);
        #endregion
    }
}
