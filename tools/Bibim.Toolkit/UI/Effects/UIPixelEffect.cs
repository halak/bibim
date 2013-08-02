using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.UI.Effects
{
    public abstract class UIPixelEffect : UIElement
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
        protected UIPixelEffect(int slotIndex, bool _, bool __)
        {
            SlotIndex = slotIndex;
        }
        #endregion

        #region Methods
        #endregion
    }
}
