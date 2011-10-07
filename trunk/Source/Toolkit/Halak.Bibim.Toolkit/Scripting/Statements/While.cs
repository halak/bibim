using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim.Scripting.Statements
{
    public sealed class While : Block
    {
        #region Fields
        private Label endLabel;
        #endregion

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
            endLabel = new Label();
        }
        #endregion

        #region Methods
        public override void Generate(BinaryScriptGenerator.Context context)
        {
            context.Write(ScriptProcess.CommandID.IfFalseThenJump);
            context.Write(Condition);
            context.WriteAddress(endLabel);
            base.Generate(context);
            context.WriteLabel(endLabel);
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
