using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Scripting.Statements
{
    public abstract class Iteration : Block
    {
        #region Properties
        public Label LoopLabel
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        protected Iteration()
            : this(null)
        {
        }

        protected Iteration(IEnumerable<Statement> statements)
            : base(statements)
        {
            LoopLabel = new Label();
        }
        #endregion
    }
}
