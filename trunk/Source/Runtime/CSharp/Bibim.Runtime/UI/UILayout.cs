using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.UI.Visuals;

namespace Bibim.UI
{
    [ClassID('U', 'I', 'L', 'T')]
    public sealed class UILayout : GameAsset
    {
        #region Fields
        #endregion

        #region Properties
        public UIVisual Root
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public UILayout()
            : this(null)
        {
        }

        public UILayout(UIVisual root)
        {
            Root = root;
        }
        #endregion

        #region Methods
        #endregion
    }
}
