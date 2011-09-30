using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Scripting.Statements
{
    public sealed class Subroutine : Block
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
                if (name != value)
                {
                    name = value ?? string.Empty;
                }
            }
        }
        #endregion

        #region Constructors
        public Subroutine()
            : this(string.Empty)
        {
        }

        public Subroutine(string name)
        {
            this.name = name ?? string.Empty;
        }
        #endregion
    }
}
