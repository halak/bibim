using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Scripting.Statements.Operators
{
    [OperatorPrecedence(2)]
    public class NegationOperator : UnaryOperator
    {
        #region Constructors
        public NegationOperator()
        {
        }

        public NegationOperator(Expression operand)
            : base(operand)
        {
        }
        #endregion

        #region Methods
        public override void Generate(BinaryScriptGenerator.Context context)
        {
            throw new NotImplementedException();
        }
        #endregion
    }
}
