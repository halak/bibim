using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim.Scripting.Statements
{
    public sealed class Continue : Statement
    {
        public override void Generate(ScriptCompiler.Context context)
        {
            context.Jump(context.CurrentBlock.BeginLabel);
        }
    }
}
