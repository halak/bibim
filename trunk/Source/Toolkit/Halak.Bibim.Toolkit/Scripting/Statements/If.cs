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
        }
        
        public If(Expression condition, IEnumerable<Statement> statements)
            : base(statements)
        {
            Condition = condition;
            ElseLabel = new Label();
        }
        #endregion

        #region Methods
        protected override void GenerateBlockBefore(BinaryScriptGenerator.Context context)
        {
            if (Condition == null)
                throw new InvalidOperationException();
        }

        protected override void GenerateBlockBegin(BinaryScriptGenerator.Context context)
        {
            if (Else != null)
                context.GenerateIfFalseThenJump(Condition, ElseLabel);
            else
                context.GenerateIfFalseThenJump(Condition, FinishLabel);
        }

        protected override void GenerateBlockEnd(BinaryScriptGenerator.Context context)
        {
            if (Else != null)
            {
                context.GenerateJump(FinishLabel);
                context.DeclareLabel(ElseLabel);
                context.Write(Else);
            }
        }
        #endregion
    }
}
