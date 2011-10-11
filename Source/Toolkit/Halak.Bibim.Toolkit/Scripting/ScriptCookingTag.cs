using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Scripting
{
    public sealed class ScriptCookingTag
    {
        #region Properties
        public string TextCode
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public ScriptCookingTag()
            : this(null)
        {
        }

        public ScriptCookingTag(string textCode)
        {
            TextCode = textCode;
        }
        #endregion
    }
}
