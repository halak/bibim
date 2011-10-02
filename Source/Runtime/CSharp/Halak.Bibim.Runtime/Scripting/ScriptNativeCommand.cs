using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim.Scripting
{
    public abstract class ScriptNativeCommand
    {
        public abstract void Execute(ScriptingContext context);
    }
}
