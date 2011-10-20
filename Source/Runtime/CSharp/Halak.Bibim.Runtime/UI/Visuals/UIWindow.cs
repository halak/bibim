using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;

namespace Bibim.UI.Visuals
{
    [ClassID('U', 'W', 'N', 'D')]
    public class UIWindow : UIPanel
    {
        #region Fields
        #endregion

        #region Properties
        public Vector2 FixedSize
        {
            get;
            set;
        }

        public bool FixedSizeUsed
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        #endregion

        #region Methods
        public void AddChild(UIVisual item)
        {
            Add(item);
        }

        public void RemoveChild(UIVisual item)
        {
            Remove(item);
        }

        public void RemoveChildAt(int index)
        {
            RemoveAt(index);
        }

        public void RemoveAllChildren()
        {
            RemoveAll();
        }
        #endregion
    }
}
