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
                //new DeclareLocalVariable("result"),
                //new DeclareLocalVariable("i"),
                new AssignmentOperator(new VariableExpression("result"), new ConstantExpression(0)),
                new AssignmentOperator(new VariableExpression("i"), new ConstantExpression(0)),
                new While(new InequalityOperator(new VariableExpression("i"), new ConstantExpression(101)), new Statement[]
                {
                    new AssignmentOperator(new VariableExpression("result"), new AdditionOperator(new VariableExpression("result"), new VariableExpression("i"))),
                    new AssignmentOperator(new VariableExpression("i"), new AdditionOperator(new VariableExpression("i"), new ConstantExpression(1))),
                }),
                new Return(new VariableExpression("result"))
            });
            
            BinaryScriptGenerator generator = new BinaryScriptGenerator();
            FileStream stream = new FileStream("Sum1To100.ab", FileMode.Create, FileAccess.Write);
            generator.Generate(stream, code);
        }
    }
}
