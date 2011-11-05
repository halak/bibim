using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Scripting.Statements.Operators
{
    public abstract class UnaryOperator : Expression
    {
        #region Properties
        public Expression Operand
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public UnaryOperator()
        {
        }

        public UnaryOperator(Expression operand)
        {
            Operand = operand;
        }
        #endregion
    }
}
