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
            Function function = context.FindFunction(Name);
            
            // return 값을 보관할 곳을 확보한다.
            context.Write(ScriptCommandID.AllocateN);
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
