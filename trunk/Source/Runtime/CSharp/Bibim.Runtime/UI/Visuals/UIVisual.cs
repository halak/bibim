using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Bibim.UI.Effects;
using Bibim.UI.Events;
using Bibim.UI.Transforms;

namespace Bibim.UI.Visuals
{
    public enum UIPositionMode : byte
    {
        Absolute,
        Relative,
        Undefined,
    }

    public enum UISizeMode : byte
    {
        Absolute,
        Relative,
        Content,
    }

    public enum UIAnchorPoint : byte
    {
        LeftTop,
        LeftBottom,
        LeftMiddle,
        RightTop,
        RightBottom,
        RightMiddle,
        CenterTop,
        CenterBottom,
        Center,
    }

    public enum UIVisibility : byte
    {
        Visible,
        Invisible,
        Collapsed,
    }

    public abstract class UIVisual : UIElement
    {
        #region Fields
        private float width;
        private float height;
        private byte opacity;
        private byte zOrder;
        #endregion

        #region Properties
        public float X
        {
            get;
            set;
        }

        public float Y
        {
            get;
            set;
        }

        public float Width
        {
            get { return width; }
            set
            {
                width = Math.Max(value, 0.0f);
            }
        }

        public float Height
        {
            get { return height; }
            set
            {
                height = Math.Max(value, 0.0f);
            }
        }

        public UIPositionMode XMode
        {
            get;
            set;
        }

        public UIPositionMode YMode
        {
            get;
            set;
        }

        public UISizeMode WidthMode
        {
            get;
            set;
        }

        public UISizeMode HeightMode
        {
            get;
            set;
        }

        public Vector2 Origin
        {
            get;
            set;
        }

        public UIAnchorPoint AnchorPoint
        {
            get;
            set;
        }

        public float Opacity
        {
            get { return (float)opacity / 255.0f; }
            set
            {
                if (value <= 0.0f)
                    opacity = 0;
                else if (value >= 1.0f)
                    opacity = 255;
                else
                    opacity = (byte)(value * 255.0f);
            }
        }

        public UIVisibility Visibility
        {
            get;
            set;
        }

        public int ZOrder
        {
            get { return (int)zOrder; }
            set
            {
                byte newValue = (byte)Math.Min(Math.Max(value, 0), 255);
                if (zOrder != newValue)
                {
                    int old = ZOrder;

                    zOrder = newValue;

                    if (Parent != null)
                        Parent.OnChildZOrderChanged(this, old);
                }
            }
        }

        public bool IsPickable
        {
            get;
            set;
        }

        public UIEventMap EventMap
        {
            get;
            set;
        }

        public UIEffectMap EffectMap
        {
            get;
            set;
        }

        public UITransform Transform
        {
            get;
            set;
        }

        public bool IsVisible
        {
            get { return Visibility == UIVisibility.Visible && opacity > 0.0f; }
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
            XMode = UIPositionMode.Absolute;
            YMode = UIPositionMode.Absolute;
            WidthMode = UISizeMode.Relative;
            HeightMode = UISizeMode.Relative;
            X = 0.0f;
            Y = 0.0f;
            Width = 1.0f;
            Height = 1.0f;
            Origin = Vector2.Zero;
            AnchorPoint = UIAnchorPoint.LeftTop;
            opacity = 255;
            Visibility = UIVisibility.Visible;
            zOrder = 128;
        }
        #endregion

        #region Methods
        public void BringToFront()
        {
            if (Parent != null)
                Parent.BringChildToFront(this);
        }

        public void SendToBack()
        {
            if (Parent != null)
                Parent.SendChildToBack(this);
        }

        private void SetBounds(float x, float y, float width, float height)
        {
            X = x;
            Y = y;
            Width = width;
            Height = height;
        }

        public void SetAbsoluteBounds(float x, float y, float width, float height)
        {
            SetBounds(x, y, width, height);
            XMode = UIPositionMode.Absolute;
            YMode = UIPositionMode.Absolute;
            WidthMode = UISizeMode.Absolute;
            HeightMode = UISizeMode.Absolute;
        }

        public void SetRelativeBounds(float x, float y, float width, float height)
        {
            SetBounds(x, y, width, height);
            XMode = UIPositionMode.Relative;
            YMode = UIPositionMode.Relative;
            WidthMode = UISizeMode.Relative;
            HeightMode = UISizeMode.Relative;
        }
        #endregion
    }
}
