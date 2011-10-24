using System;
using System.Collections.Generic;
using System.Text;
using Bibim.UI.Frames;

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

        public bool StateSizeReferenced
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public UIButton()
        {
            NormalWindow = new UIWindow() { Frame = new UIFittedFrame() };
            PushedWindow = new UIWindow() { Frame = new UIFittedFrame() };
            HoveringWindow = new UIWindow(){ Frame = new UIFittedFrame() };
            Add(NormalWindow);
            Add(PushedWindow);
            Add(HoveringWindow);
        }
        #endregion

        #region Methods
        #endregion
    }
}
