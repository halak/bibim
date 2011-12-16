using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.UI.Visuals
{
    [ClassID('U', 'B', 'T', 'N')]
    public class UIButton : UIPanel
    {
        public enum StateCode
        {
            Normal,
            Pushed,
            Hovering,
        };

        #region Fields
        private StateCode state;
        #endregion

        #region Properties
        public StateCode State
        {
            get { return state; }
            private set
            {
                if (state != value)
                {
                    state = value;
                }
            }
        }

        public UIVisual Normal
        {
            get;
            set;
        }

        public UIVisual Pushed
        {
            get;
            set;
        }

        public UIVisual Hovering
        {
            get;
            set;
        }

        public bool HideInactives
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public UIButton()
        {
        }
        #endregion

        #region Methods
        #endregion
    }
}
