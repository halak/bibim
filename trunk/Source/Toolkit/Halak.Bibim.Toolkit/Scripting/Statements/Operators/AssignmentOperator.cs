using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Scripting.Statements.Operators
{
    [OperatorPrecedence(14)]
    public sealed class AssignmentOperator : Expression
    {
        #region Properties
        public VariableExpression Variable
        {
            get;
            set;
        }

        public Expression Value
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public AssignmentOperator()
        {
        }

        public AssignmentOperator(VariableExpression variable, Expression value)
        {
            Variable = variable;
            Value = value;
        }
        #endregion

        #region Methods
        public override void Generate(BinaryScriptGenerator.Context context)
        {
            if (Variable == null)
                throw new InvalidOperationException();
            if (Value == null)
                throw new InvalidOperationException();

            context.Write(Value);
            int stackIndex;
            int localOffset;
            int size;
            if (context.TryGetVariableOffsetFromStack(Variable.Name, out stackIndex, out localOffset, out size))
            {
                context.GenerateLocalAssign(stackIndex, localOffset);
            }
            else
            {
                context.Write(ScriptInstruction.GlobalAssign);
                context.Write(Variable.Name);
            }
        }

        public override string ToString()
        {
            if (Variable != null && Value != null)
                return string.Format("{0} = {1}", Variable.ToString(), Value.ToString());
            else
                return base.ToString();
        }
        #endregion
    }
}
