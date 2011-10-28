using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.UI.Effects
{
    public abstract class UIEffect : UIElement
    {
        #region Fields
        #endregion

        #region Properties
        public int SlotIndex
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        protected UIEffect(int slotIndex)
        {
            SlotIndex = slotIndex;
        }
        #endregion

        #region Methods
        #endregion
    }
}
