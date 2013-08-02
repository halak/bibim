using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Typography;

namespace Bibim.UI.Visuals
{
    [ClassID('U', 'L', 'B', 'L')]
    public class UILabel : UIVisual
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
