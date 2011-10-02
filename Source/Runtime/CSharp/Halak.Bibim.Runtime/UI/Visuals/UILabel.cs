using System;
using System.Collections.Generic;
using System.Text;
using Halak.Bibim.Typography;

namespace Halak.Bibim.UI.Visuals
{
    [ClassID('U', 'L', 'B', 'L')]
    public sealed class UILabel : UIVisual
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

        public Font Font
        {
            get;
            set;
        }

        public bool AutoResize
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public UILabel()
        {
            text = string.Empty;
        }
        #endregion

        #region Methods
        #endregion
    }
}
