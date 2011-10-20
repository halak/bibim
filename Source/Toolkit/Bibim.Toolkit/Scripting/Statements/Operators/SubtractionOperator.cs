using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Scripting.Statements.Operators
{
    [OperatorPrecedence(4)]
    public sealed class SubtractionOperator : BinaryOperator
    {
        #region Constructors
        public SubtractionOperator()
        {
        }

        public SubtractionOperator(Expression leftOperand, Expression rightOperand)
            : base(leftOperand, rightOperand)
        {
        }
        #endregion

        #region Methods
        public override void Generate(ScriptCompiler.Context context)
        {
            Generate(context, ScriptInstruction.SubtractInt);
        }

        public override string ToString()
        {
            return string.Format("{0} - {1}", ToString(LeftOperand), ToString(RightOperand));
        }
        #endregion
    }
}
