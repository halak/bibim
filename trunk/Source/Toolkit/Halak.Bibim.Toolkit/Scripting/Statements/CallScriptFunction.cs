using System;
using System.Collections.Generic;
using System.Text;
using Halak.Bibim.IO;

namespace Halak.Bibim.Scripting.Statements
{
    public sealed class CallScriptFunction : CallBase
    {
        #region Constructors
        public CallScriptFunction()
        {
        }

        public CallScriptFunction(string name)
            : base(name)
        {
        }

        public CallScriptFunction(string name, Expression[] arguments)
            : base(name, arguments)
        {
        }
        #endregion

        public override void Generate(ScriptCompiler.Context context)
        {
            context.CallScriptFunction(Name, Arguments);
        }
    }
}
