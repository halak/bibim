using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Scripting.Statements
{
    public sealed class Label : Statement
    {
        #region Fields
        private string name;
        #endregion

        #region Properties
        private string Name
        {
            get { return name; }
            set
            {
                name = value ?? string.Empty;
            }
        }
        #endregion

        #region Constructor
        public Label()
            : this(string.Empty)
        {
        }

        public Label(string name)
        {
            Name = name;
        }
        #endregion

        #region Methods
        public override void Generate(BinaryScriptGenerator.Context context)
        {
            throw new InvalidOperationException("must call WriteLabel or WriteAddress");
        }
        #endregion
    }
}
