using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Scripting.Statements
{
    public sealed class Break : Statement
    {
        public override void Generate(ScriptCompiler.Context context)
        {
            context.Jump(context.CurrentBlock.EndLabel);
        }
    }
}
