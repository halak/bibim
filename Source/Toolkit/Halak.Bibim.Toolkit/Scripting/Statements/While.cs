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

        public Label StartLabel
        {
            get;
            private set;
        }

        public Label FinishLabel
        {
            get;
            private set;
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
            StartLabel = new Label();
            FinishLabel = new Label();
        }
        #endregion

        #region Methods
        public override void Generate(BinaryScriptGenerator.Context context)
        {
            context.WriteLabel(StartLabel);
            context.Write(Condition);
            context.Write(ScriptCommandID.IfFalseThenJump);
            context.WriteAddress(FinishLabel);

            base.Generate(context);

            context.Write(ScriptCommandID.Jump);
            context.WriteAddress(StartLabel);
            context.WriteLabel(FinishLabel);
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
