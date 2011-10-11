using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim.Scripting.Statements
{
    public sealed class Continue : Statement
    {
        public override void Generate(ScriptCompiler.Context context)
        {
            Iteration iterationBlock = FindIterationBlock(context);
            if (iterationBlock != null)
                context.Jump(iterationBlock.LoopLabel);
            else
                throw new InvalidOperationException("continue must be in iteration block");
        }

        private Iteration FindIterationBlock(ScriptCompiler.Context context)
        {
            for (int i = context.CurrentBlocks.Count - 1; i >= 0; i--)
            {
                if (context.CurrentBlocks[i] is Iteration)
                    return ((Iteration)context.CurrentBlocks[i]);
            }

            return null;
        }
    }
}
