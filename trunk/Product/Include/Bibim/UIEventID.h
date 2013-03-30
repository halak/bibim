#pragma once
#ifndef __BIBIM_UIEVENTID_H__
#define __BIBIM_UIEVENTID_H__

#   include <Bibim/FWD.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class UIEventID
        {
            public:
                enum Type
                {
                    UnknownType = 0,
                    KeyDownType = 1,
                    KeyUpType = 2,
                    KeyPressingType = 3,
                    MouseEnterType = 4,
                    MouseLeaveType = 5,
                    MouseMoveType = 6,
                    MouseButtonDownType = 7,
                    MouseButtonUpType = 8,
                    MouseButtonPressingType = 9,
                    MouseWheelType = 10,
                    MouseClickType = 11,
                    GamePadButtonDownType = 12,
                    GamePadButtonUpType = 13,
                    GamePadButtonPressingType = 14,
                    GamePadTriggerType = 15,
                    GamePadThumbstickType = 16,
                    FocusedType = 17,
                    BluredType = 18,
                    ApplicationType = 19,
                };

                static const UIEventID Unknown;
                static const UIEventID KeyDown;
                static const UIEventID KeyUp;
                static const UIEventID KeyPressing;
                static const UIEventID MouseEnter;
                static const UIEventID MouseLeave;
                static const UIEventID MouseMove;
                static const UIEventID MouseButtonDown;
                static const UIEventID MouseButtonUp;
                static const UIEventID MouseButtonPressing;
                static const UIEventID MouseWheel;
                static const UIEventID MouseClick;
                static const UIEventID GamePadButtonDown;
                static const UIEventID GamePadButtonUp;
                static const UIEventID GamePadButtonPressing;
                static const UIEventID GamePadTrigger;
                static const UIEventID GamePadThumbstick;
                static const UIEventID Focused;
                static const UIEventID Blured;

            public:
                inline UIEventID();
                inline explicit UIEventID(Type type);
                inline explicit UIEventID(const String& name);
                inline UIEventID(const UIEventID& original);
                inline ~UIEventID();

                inline Type GetType() const;
                inline const String& GetName() const;

                inline UIEventID& operator = (const UIEventID& right);
                inline bool operator == (const UIEventID& right) const;
                inline bool operator != (const UIEventID& right) const;
                inline bool operator < (const UIEventID& right) const;

            public:
                static const String& ConvertFromTypeToName(Type type);
                static Type ConvertFromNameToType(const String& name);

            private:
                Type type;
                String name;

                static const String EventNames[ApplicationType];
        };
    }

#   include <Bibim/UIEventID.inl>

#endif