using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Scripting.Statements
{
    public sealed class VariableExpression : Expression
    {
        #region Fields
        private string name;
        #endregion

        #region Properties
        public string Name
        {
            get { return name; }
            set
            {
                name = value ?? string.Empty;
            }
        }
        #endregion

        #region Constructors
        public VariableExpression()
            : this(string.Empty)
        {
        }

        public VariableExpression(string name)
        {
            this.name = name ?? string.Empty;
        }
        #endregion

        #region Methods
        public override void Generate(ScriptCompiler.Context context)
        {
            context.PushVariable(Name);
        }

        public override string ToString()
        {
            return Name;
        }
        #endregion
    }
}
