using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Scripting.Statements
{
    public abstract class Expression : Statement
    {
        public virtual ScriptObjectType GuessResultType(ScriptCompiler.Context context) { return ScriptObjectType.Void; }
    }
}
