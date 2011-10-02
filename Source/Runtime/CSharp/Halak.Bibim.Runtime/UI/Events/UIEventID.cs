using System;
using System.Collections.Generic;
using System.Text;

namespace Halak.Bibim.UI.Events
{
    public struct UIEventID
    {
        #region TypeCode
        public enum TypeCode
        {
            Unknown = 0,
            KeyDown = 1,
            KeyUp = 2,
            KeyPressing = 3,
            MouseEnter = 4,
            MouseLeave = 5,
            MouseMove = 6,
            MouseButtonDown = 7,
            MouseButtonUp = 8,
            MouseButtonPressing = 9,
            MouseWheel = 10,
            MouseClick = 11,
            GamePadButtonDown = 12,
            GamePadButtonUp = 13,
            GamePadButtonPressing = 14,
            GamePadTrigger = 15,
            GamePadThumbstick = 16,
            Application = 17,
        }
        #endregion

        public static readonly UIEventID Unknown;
        public static readonly UIEventID KeyDown;
        public static readonly UIEventID KeyUp;
        public static readonly UIEventID KeyPressing;
        public static readonly UIEventID MouseEnter;
        public static readonly UIEventID MouseLeave;
        public static readonly UIEventID MouseMove;
        public static readonly UIEventID MouseButtonDown;
        public static readonly UIEventID MouseButtonUp;
        public static readonly UIEventID MouseButtonPressing;
        public static readonly UIEventID MouseWheel;
        public static readonly UIEventID MouseClick;
        public static readonly UIEventID GamePadButtonDown;
        public static readonly UIEventID GamePadButtonUp;
        public static readonly UIEventID GamePadButtonPressing;
        public static readonly UIEventID GamePadTrigger;
        public static readonly UIEventID GamePadThumbstick;
    }
}
