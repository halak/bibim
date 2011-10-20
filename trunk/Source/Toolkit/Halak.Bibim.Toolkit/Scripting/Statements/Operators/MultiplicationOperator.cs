using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Scripting.Statements.Operators
{
    [OperatorPrecedence(3)]
    public sealed class MultiplicationOperator : BinaryOperator
    {
        #region Constructors
        public MultiplicationOperator()
        {
        }

        public MultiplicationOperator(Expression leftOperand, Expression rightOperand)
            : base(leftOperand, rightOperand)
        {
        }
        #endregion

        #region Methods
        public override void Generate(ScriptCompiler.Context context)
        {
            Generate(context, ScriptInstruction.MultiplyInt);
        }

        public override string ToString()
        {
            return string.Format("{0} * {1}", ToString(LeftOperand), ToString(RightOperand));
        }
        #endregion
    }
}
