using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Scripting.Statements
{
    public sealed class LocalVariableExpression : VariableExpression
    {
        #region Constructors
        public LocalVariableExpression()
        {
        }

        public LocalVariableExpression(string name)
            : base(name)
        {
        }
        #endregion

        #region Methods
        public override void Generate(BinaryScriptGenerator.Context context)
        {
            throw new NotImplementedException();
        }

        public override string ToString()
        {
            return '$' + Name;
        }
        #endregion
    }
}
