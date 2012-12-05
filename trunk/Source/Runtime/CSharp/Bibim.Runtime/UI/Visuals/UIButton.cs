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
        private UIVisual normal;
        private UIVisual pushed;
        private UIVisual hovering;
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
            get { return normal; }
            set
            {
                if (normal != value)
                {
                    if (normal != null)
                        Remove(normal);

                    normal = value;

                    if (normal != null)
                        Add(normal);
                }
            }
        }

        public UIVisual Pushed
        {
            get { return pushed; }
            set
            {
                if (pushed != value)
                {
                    if (pushed != null)
                        Remove(pushed);

                    pushed = value;

                    if (pushed != null)
                        Add(pushed);
                }
            }
        }

        public UIVisual Hovering
        {
            get { return hovering; }
            set
            {
                if (hovering != value)
                {
                    if (hovering != null)
                        Remove(hovering);

                    hovering = value;

                    if (hovering != null)
                        Add(hovering);
                }
            }
        }

        public bool HideInactives
        {
            get;
            set;
        }

        public bool FocusVisible
        {
            get;
            set;
        }

        public bool IsFrozen
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public UIButton()
        {
            HideInactives = true;
            FocusVisible = false;
        }
        #endregion

        #region Methods
        #endregion
    }
}
