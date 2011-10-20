using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Bibim.UI.Events;
using Bibim.UI.Frames;
using Bibim.UI.Transforms;

namespace Bibim.UI.Visuals
{
    public abstract class UIVisual : UIElement
    {
        #region Fields
        private float opacity;
        #endregion

        #region Properties
        public bool Shown
        {
            get;
            set;
        }

        public float Opacity
        {
            get { return opacity; }
            set
            {
                opacity = MathHelper.Clamp(value, 0.0f, 1.0f);
            }
        }

        public Vector2 Size
        {
            get;
            set;
        }

        public UIFrame Frame
        {
            get;
            set;
        }

        public UITransform Transform
        {
            get;
            set;
        }

        public UIEventMap EventMap
        {
            get;
            set;
        }

        public bool IsVisible
        {
            get { return Shown && opacity > 0.0f; }
        }

        public UIPanel Parent
        {
            get;
            internal set;
        }
        #endregion

        #region Constructors
        public UIVisual()
        {
            Opacity = 1.0f;
            Shown = true;
        }
        #endregion

        #region Methods
        #endregion
    }
}
