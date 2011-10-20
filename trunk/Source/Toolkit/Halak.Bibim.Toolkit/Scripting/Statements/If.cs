using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Scripting.Statements
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
        #endregion

        #region Constructors
        public If()
            : this(null, null)
        {
        }

        public If(Expression condition)
            : this(condition, null)
        {
        }
        
        public If(Expression condition, IEnumerable<Statement> statements)
            : base(statements)
        {
            Condition = condition;
            ElseLabel = new Label();

            BeginLabel.Name = "If";
            EndLabel.Name = "End If";
            ElseLabel.Name = "Else";
        }
        #endregion

        #region Methods
        protected override void GenerateBlockBefore(ScriptCompiler.Context context)
        {
            if (Condition == null)
                throw new InvalidOperationException();
        }

        protected override void GenerateBlockBegin(ScriptCompiler.Context context)
        {
            if (Else != null)
                context.IfFalseThenJump(Condition, ElseLabel);
            else
                context.IfFalseThenJump(Condition, EndLabel);
        }

        protected override void GenerateBlockEnd(ScriptCompiler.Context context)
        {
            if (Else != null)
            {
                context.Jump(EndLabel);
                context.InidicateLabel(ElseLabel);
                context.Generate(Else);
            }
        }
        #endregion
    }
}
