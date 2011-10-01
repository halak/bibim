using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.UI.Visuals
{
    [ClassID('U', 'S', 'P', 'R')]
    public sealed class UISprite : UIVisual
    {
        #region Fields
        #endregion

        #region Properties
        public UIImage Image
        {
            get;
            set;
        }

        public bool AutoResize
        {
            get;
            set;
        }

        public bool HorizontalFlip
        {
            get;
            set;
        }

        public bool VerticalFlip
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
