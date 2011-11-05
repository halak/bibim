using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Scripting
{
    [AttributeUsage(AttributeTargets.Class)]
    public sealed class ScriptNativeLibraryAttribute : Attribute
    {
        #region Properties
        public string Name
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public ScriptNativeLibraryAttribute()
            : this(string.Empty)
        {
        }

        public ScriptNativeLibraryAttribute(string name)
        {
            Name = name ?? string.Empty;
        }
        #endregion
    }
}
