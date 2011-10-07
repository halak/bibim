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
            throw new NotImplementedException();
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
