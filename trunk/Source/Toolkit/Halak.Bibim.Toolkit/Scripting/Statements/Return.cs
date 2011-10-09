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
        public override void Generate(BinaryScriptGenerator.Context context)
        {
            context.Write(Value);
            context.Write(ScriptCommandID.LocalAssign);
            context.Write(-1 - context.Function.Parameters.Count - 3);
            int zero = 0;
            context.Write(zero);
            context.Write(ScriptCommandID.Return);
        }
        #endregion
    }
}
