using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim.Scripting.Statements
{
    public sealed class Return : Statement
    {
        #region Properties
        public Expression Value
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public Return()
        {
        }

        public Return(Expression value)
        {
            Value = value;
        }
        #endregion

        #region Methods
        public override void Generate(ScriptCompiler.Context context)
        {
            context.Return(Value);
        }
        #endregion
    }
}
