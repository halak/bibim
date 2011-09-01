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
                    UnknownType,
                    KeyDownType,
                    KeyUpType,
                    KeyPressingType,
                    MouseEnterType,
                    MouseLeaveType,
                    MouseMoveType,
                    MouseButtonDownType,
                    MouseButtonUpType,
                    MouseButtonPressingType,
                    MouseWheelType,
                    MouseClickType,
                    GamePadButtonDownType,
                    GamePadButtonUpType,
                    GamePadButtonPressingType,
                    GamePadTriggerType,
                    GamePadThumbstickType,
                    ApplicationType,
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