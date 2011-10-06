using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Scripting
{
    [AttributeUsage(AttributeTargets.Class)]
    public sealed class ScriptFunctionLibraryAttribute : Attribute
    {
        #region Properties
        public string Name
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public ScriptFunctionLibraryAttribute()
            : this(string.Empty)
        {
        }

        public ScriptFunctionLibraryAttribute(string name)
        {
            Name = name ?? string.Empty;
        }
        #endregion
    }
}
