using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Scripting.Statements
{
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = false, Inherited = true)]
    public sealed class OperatorPrecedenceAttribute : Attribute
    {
        #region Properties
        public uint Rank
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public OperatorPrecedenceAttribute(uint rank)
        {
            Rank = rank;
        }
        #endregion
    }
}
