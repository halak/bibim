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
            // Stack layout in Function call (Top-down)
            // ==============================
            // 1st Return value space
            // ------------------------------
            // 2nd Return value space
            // ------------------------------
            // ...
            // ------------------------------
            // N Return value space
            // ==============================
            // 1st Argument
            // ------------------------------
            // 2nd Argument
            // ------------------------------
            // ...
            // ------------------------------
            // N Argument
            // ==============================
            // Caller-address
            // ==============================
            // Number of arugments
            // ==============================
            // 1st Local variable
            // 2nd Local variable
            // ...
            // N Local variable
            // ==============================

            Function function = context.FindFunction(Name);

            // return value들을 보관할 영역을 확보합니다.
            foreach (ScriptObjectType item in function.ReturnTypes)
                context.AllocateN(DeclareVariable.SizeOf(item), true);
            GeneratePushArguments(context);
            context.Write(ScriptInstruction.CallScriptFunction);
            context.WriteAddress(function.BeginLabel);
            context.Write(Arguments.Length);
        }
    }
}
