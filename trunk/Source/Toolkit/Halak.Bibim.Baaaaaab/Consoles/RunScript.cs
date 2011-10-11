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
        public static int Factorial(int N)
        {
            if (N <= 0)
                return 0;
            else if (N == 1)
                return 1;
            else
                return N * Factorial(N - 1);
        }

        public static void Run([Alias("file")] string filename)
        {
            Block code = new Block(new Statement[]
            {
                new Function("Sum1To100", null, new ScriptObjectType[] { ScriptObjectType.Int }, new Statement[]
                {
                    new DeclareVariable("result", ScriptObjectType.Int),
                    new DeclareVariable("i", ScriptObjectType.Int),
                    new CallNativeFunction("Print", new ConstantExpression("Hello Malthm !")),
                    new AssignmentOperator(new VariableExpression("result"), new ConstantExpression(0)),
                    new AssignmentOperator(new VariableExpression("i"), new ConstantExpression(0)),
                    new While(new InequalityOperator(new VariableExpression("i"), new ConstantExpression(101)), new Statement[]
                    {
                        new AssignmentOperator(new VariableExpression("result"), new AdditionOperator(new VariableExpression("result"), new VariableExpression("i"))),
                        new AssignmentOperator(new VariableExpression("i"), new AdditionOperator(new VariableExpression("i"), new ConstantExpression(1))),
                    }),
                    new Return(new VariableExpression("result"))
                }),

                new Function("Factorial", new DeclareVariable[] { new DeclareVariable("N", ScriptObjectType.Int) }, new ScriptObjectType[] { ScriptObjectType.Int }, new Statement[]
                {
                    new If(new EqualityOperator(new VariableExpression("N"), new ConstantExpression(0)), new Statement[]
                    {
                        new Return(new ConstantExpression(0))
                    })
                    {
                    Else = new If(new EqualityOperator(new VariableExpression("N"), new ConstantExpression(1)), new Statement[]
                    {
                        new Return(new ConstantExpression(1))
                    })
                    {
                    Else = new Block(new Statement[]
                    {
                        new Return(new MultiplicationOperator(new VariableExpression("N"), new CallScriptFunction("Factorial", new Expression[] { new SubtractionOperator(new VariableExpression("N"), new ConstantExpression(1)) })))
                    })
                    }
                    },
                })
            });

            ScriptNativeFunctionTable.Rebuild();
            ScriptCompiler compiler = new ScriptCompiler();
            FileStream fs = new FileStream("Script.ab", FileMode.Create, FileAccess.Write);

            ScriptWriter writer = new ScriptWriter();
            string text;
            writer.Write(new Asset.AssetStreamWriter(fs, null), compiler.Compile(code, out text));
            fs.Close();
        }
    }
}
