using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Input;

namespace Bibim.UI.Visuals
{
    [ClassID('U', 'E', 'D', 'T')]
    public sealed class UIEditText : UILabel
    {
        #region Properties
        public IME.TextFormat Format
        {
            get;
            set;
        }

        public string Placeholder
        {
            get;
            set;
        }

        public int MaxLength
        {
            get;
            set;
        }

        public bool Frozen
        {
            get;
            set;
        }

        public string EditorTitle
        {
            get;
            set;
        }

        public string EditorDescription
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public UIEditText()
        {
            Format = IME.TextFormat.Default;
            Placeholder = string.Empty;
            MaxLength = 0;
            Frozen = false;
            EditorTitle = string.Empty;
            EditorDescription = string.Empty;
        }
        #endregion

        #region Methods
        #endregion
    }
}
