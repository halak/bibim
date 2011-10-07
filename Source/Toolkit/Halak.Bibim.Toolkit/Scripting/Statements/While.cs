using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim.Scripting.Statements
{
    public sealed class While : Block
    {
        #region Properties
        public Expression Condition
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public While()
        {
        }

        public While(Expression condition)
        {
            Condition = condition;
        }

        public While(Expression condition, IEnumerable<Statement> statements)
            : base(statements)
        {
            Condition = condition;
        }
        #endregion

        #region Methods
        public override string ToString()
        {
            if (Condition != null)
                return string.Format("while ({0})", Condition.ToString());
            else
                return base.ToString();
        }
        #endregion
    }
}
