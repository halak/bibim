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

            int index = context.GetLocalVariableIndex(Variable.Name);
            if (index != -1)
            {
            }
            else
            {
            }

            if (Variable is GlobalVariableExpression)
            {
                context.Write(ScriptProcess.CommandID.GlobalAssignmentOperator);
                context.Write(Variable.Name);
            }
            else if (Variable is LocalVariableExpression)
            {
                context.Write(ScriptProcess.CommandID.LocalAssignmentOperator);
                context.Write(Variable);
            }
            else
                throw new InvalidOperationException();

            context.Write(Value);
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
