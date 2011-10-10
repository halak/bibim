using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim.Scripting.Statements
{
    public sealed class While : Iteration
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

            BeginLabel.Name = "While";
            EndLabel.Name = "End While";
            LoopLabel.Name = "While-Loop";
        }
        #endregion

        #region Methods
        protected override void GenerateBlockBefore(ScriptCompiler.Context context)
        {
            if (Condition == null)
                throw new InvalidOperationException("Condition");
        }

        protected override void GenerateBlockBegin(ScriptCompiler.Context context)
        {
            context.IfFalseThenJump(Condition, EndLabel);
        }

        protected override void GenerateBlockEnd(ScriptCompiler.Context context)
        {
            context.Jump(BeginLabel);
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
