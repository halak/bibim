﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Scripting.Statements
{
    public sealed class Comment : Statement
    {
        #region Fields
        private string text;
        #endregion

        #region Properties
        public string Text
        {
            get { return text; }
            set
            {
                text = value ?? string.Empty;
            }
        }
        #endregion

        #region Constructors
        public Comment()
            : this(string.Empty)
        {
        }

        public Comment(string text)
        {
            this.text = text ?? string.Empty;
        }
        #endregion
    }
}
