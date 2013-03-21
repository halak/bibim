using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.UI.Visuals
{
    [ClassID('U', 'S', 'C', 'P')]
    public class UIScrollablePanel : UIPanel
    {
        #region Fields
        private UIVisual content;
        #endregion

        #region Properties
        public UIVisual Content
        {
            get { return content; }
            set
            {
                if (content != value)
                {
                    if (content != null)
                        Remove(content);

                    content = value;

                    if (content != null)
                        Add(content);
                }
            }
        }
        #endregion

        #region Constructors
        public UIScrollablePanel()
        {
        }
        #endregion

        #region Methods
        #endregion
    }
}
