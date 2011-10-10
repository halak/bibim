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
            : this(null, null)
        {
        }

        public While(Expression condition)
            : this(condition, null)
        {
        }

        public While(Expression condition, IEnumerable<Statement> statements)
            : base(statements)
        {
            Condition = condition;
        }
        #endregion

        #region Methods
        protected override void GenerateBlockBefore(BinaryScriptGenerator.Context context)
        {
            if (Condition == null)
                throw new InvalidOperationException("Condition");
        }

        protected override void GenerateBlockBegin(BinaryScriptGenerator.Context context)
        {
            context.GenerateIfFalseThenJump(Condition, FinishLabel);
        }

        protected override void GenerateBlockEnd(BinaryScriptGenerator.Context context)
        {
            context.GenerateJump(StartLabel);
        }

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
