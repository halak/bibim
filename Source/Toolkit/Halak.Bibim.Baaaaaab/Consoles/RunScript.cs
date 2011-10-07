using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using Halak.Bibim.Scripting;
using Halak.Bibim.Scripting.Statements;
using Halak.Bibim.Scripting.Statements.Operators;
using Halak.Bibim.Toolkit;

namespace Halak.Bibim.Bab.Consoles
{
    [ConsoleEntryPoint]
    [Alias("script")]
    public static class RunScript
    {
        public static void Run([Alias("file")] string filename)
        {
            Function code = new Function("Sum1To100", new Statement[]
            {
                new AssignmentOperator(new LocalVariableExpression("result"), new ConstantExpression(0)),
                new AssignmentOperator(new LocalVariableExpression("i"), new ConstantExpression(0)),
                new While(new InequalityOperator(new LocalVariableExpression("i"), new ConstantExpression(101)), new Statement[]
                {
                    new AssignmentOperator(new LocalVariableExpression("result"), new AdditionOperator(new LocalVariableExpression("result"), new LocalVariableExpression("i"))),
                    new AssignmentOperator(new LocalVariableExpression("i"), new AdditionOperator(new LocalVariableExpression("i"), new ConstantExpression(1))),
                }),
                new Return(new LocalVariableExpression("result"))
            });
            
            BinaryScriptGenerator generator = new BinaryScriptGenerator();
            FileStream stream = new FileStream("Sum1To100.ab", FileMode.Create, FileAccess.Write);
            generator.Generate(stream, code);
        }
    }
}
