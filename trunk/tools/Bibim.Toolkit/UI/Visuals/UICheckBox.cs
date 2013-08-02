using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.UI.Visuals
{
    [ClassID('U', 'C', 'B', 'X')]
    public class UICheckBox : UIButton
    {
        #region Fields
        private UIVisual checkedNormal;
        private UIVisual checkedPushed;
        private UIVisual checkedHovering;
        #endregion

        #region Properties
        public UIVisual CheckedNormal
        {
            get { return checkedNormal; }
            set
            {
                if (checkedNormal != value)
                {
                    if (checkedNormal != null)
                        Remove(checkedNormal);

                    checkedNormal = value;

                    if (checkedNormal != null)
                        Add(checkedNormal);
                }
            }
        }

        public UIVisual CheckedPushed
        {
            get { return checkedPushed; }
            set
            {
                if (checkedPushed != value)
                {
                    if (checkedPushed != null)
                        Remove(checkedPushed);

                    checkedPushed = value;

                    if (checkedPushed != null)
                        Add(checkedPushed);
                }
            }
        }

        public UIVisual CheckedHovering
        {
            get { return checkedHovering; }
            set
            {
                if (checkedHovering != value)
                {
                    if (checkedHovering != null)
                        Remove(checkedHovering);

                    checkedHovering = value;

                    if (checkedHovering != null)
                        Add(checkedHovering);
                }
            }
        }

        public bool IsChecked
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
