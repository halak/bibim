using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Scripting.Statements.Operators
{
    [OperatorPrecedence(7)]
    public sealed class InequalityOperator : BinaryOperator
    {
        #region Constructors
        public InequalityOperator()
        {
        }

        public InequalityOperator(Expression leftOperand, Expression rightOperand)
            : base(leftOperand, rightOperand)
        {
        }
        #endregion

        #region Methods
        public override void Generate(BinaryScriptGenerator.Context context)
        {
            Generate(context, ScriptProcess.CommandID.InequalityOperator);
        }

        public override string ToString()
        {
            return string.Format("{0} != {1}", ToString(LeftOperand), ToString(RightOperand));
        }
        #endregion
    }
}
