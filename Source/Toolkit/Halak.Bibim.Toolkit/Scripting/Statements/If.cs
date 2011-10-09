using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim.Scripting.Statements
{
    public sealed class If : Block
    {
        #region Properties
        public Expression Condition
        {
            get;
            set;
        }

        public Block Else
        {
            get;
            set;
        }

        public Label ElseLabel
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
        public If()
            : this(null, null)
        {
        }

        public If(Expression condition)
            : this(condition, null)
        {
            ElseLabel = new Label();
            FinishLabel = new Label();
        }
        
        public If(Expression condition, IEnumerable<Statement> statements)
            : base(statements)
        {
            Condition = condition;
            ElseLabel = new Label();
            FinishLabel = new Label();
        }
        #endregion

        #region Methods
        public override void Generate(BinaryScriptGenerator.Context context)
        {
            if (Condition == null)
                throw new InvalidOperationException();

            if (Else != null)
            {
                context.Write(ScriptCommandID.IfFalseThenJump);
                context.WriteAddress(ElseLabel);
                context.Write(Condition);

                base.Generate(context);

                context.Write(ScriptCommandID.Jump);
                context.WriteAddress(FinishLabel);
                context.WriteLabel(ElseLabel);
                context.Write(Else);
                context.WriteLabel(FinishLabel);
            }
            else
            {
                context.Write(ScriptCommandID.IfFalseThenJump);
                context.WriteAddress(FinishLabel);
                context.Write(Condition);

                base.Generate(context);

                context.WriteLabel(FinishLabel);
            }
        }
        #endregion
    }
}
