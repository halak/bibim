using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Scripting.Statements
{
    public sealed class GlobalVariableExpression : VariableExpression
    {
        #region Constructors
        public GlobalVariableExpression()
        {
        }

        public GlobalVariableExpression(string name)
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
            return Name;
        }
        #endregion
    }
}
