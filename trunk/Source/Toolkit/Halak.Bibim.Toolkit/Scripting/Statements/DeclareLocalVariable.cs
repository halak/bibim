using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Scripting.Statements
{
    public sealed class DeclareLocalVariable : Statement
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
        public DeclareLocalVariable()
            : this(string.Empty)
        {
        }

        public DeclareLocalVariable(string name)
        {
            Name = name;
        }
        #endregion

        #region Methods
        public override void Generate(BinaryScriptGenerator.Context context)
        {
        }
        #endregion
    }
}
