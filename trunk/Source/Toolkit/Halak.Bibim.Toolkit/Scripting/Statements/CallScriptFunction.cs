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

        public override void Generate(BinaryScriptGenerator.Context context)
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
            
            // return 값을 보관할 곳을 확보한다.
            context.Write(ScriptInstruction.AllocateN);
            int returnValueSize = 0;
            foreach (ScriptObjectType item in function.ReturnTypes)
                returnValueSize += DeclareVariable.SizeOf(item);
            context.Write(returnValueSize);

            GenerateArguments(context);
            context.WriteAddress(function.StartLabel);
            context.Write(Arguments.Length);
        }
    }
}
