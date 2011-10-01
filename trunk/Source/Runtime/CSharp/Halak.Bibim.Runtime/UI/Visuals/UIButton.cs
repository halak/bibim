using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.UI.Visuals
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

        public UIWindow NormalWindow
        {
            get;
            private set;
        }

        public UIWindow PushedWindow
        {
            get;
            private set;
        }

        public UIWindow HoveringWindow
        {
            get;
            private set;
        }

        public bool HideInactives
        {
            get;
            set;
        }

        public bool stateSizeReferenced
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        #endregion

        #region Methods
        #endregion
    }
}
