#pragma once
#ifndef __BIBIM_UIMOUSEEVENTARGS_H__
#define __BIBIM_UIMOUSEEVENTARGS_H__

#include <Bibim/FWD.h>
#include <Bibim/UIEventArgs.h>
#include <Bibim/Point2.h>
#include <Bibim/Rect.h>

namespace Bibim
{
    class UIMouseEventArgs : public UIEventArgs
    {
        public:
            UIMouseEventArgs();
            UIMouseEventArgs(UIMouseEventDispatcher* dispatcher, UIVisual* target);
            UIMouseEventArgs(UIMouseEventDispatcher* dispatcher, UIVisual* target, Point2 position, Point2 movement);
            UIMouseEventArgs(UIMouseEventDispatcher* dispatcher, UIVisual* target, Point2 position, Point2 movement, bool isLeftButtonPressed, bool isRightButtonPressed, bool isMiddleButtonPressed);
            UIMouseEventArgs(const UIMouseEventArgs& original);
            virtual ~UIMouseEventArgs();

            virtual UIMouseEventArgs* Clone() const;

            virtual void Serialize(Serializer& context) const;

            inline UIMouseEventDispatcher* GetDispatcher() const;
            inline Point2 GetPosition() const;
            inline Point2 GetMovement() const;
            inline int GetPositionX() const;
            inline int GetPositionY() const;
            inline int GetMovementX() const;
            inline int GetMovementY() const;
            inline bool IsLeftButtonPressed() const;
            inline bool IsRightButtonPressed() const;
            inline bool IsMiddleButtonPressed() const;

        private:
            UIMouseEventDispatcher* dispatcher;
            Point2 position;
            Point2 movement;
            bool isLeftButtonPressed;
            bool isRightButtonPressed;
            bool isMiddleButtonPressed;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIMouseEventDispatcher* UIMouseEventArgs::GetDispatcher() const
    {
        return dispatcher;
    }

    Point2 UIMouseEventArgs::GetPosition() const
    {
        return position;
    }

    Point2 UIMouseEventArgs::GetMovement() const
    {
        return movement;
    }

    int UIMouseEventArgs::GetPositionX() const
    {
        return position.X;
    }

    int UIMouseEventArgs::GetPositionY() const
    {
        return position.Y;
    }

    int UIMouseEventArgs::GetMovementX() const
    {
        return movement.X;
    }

    int UIMouseEventArgs::GetMovementY() const
    {
        return movement.Y;
    }

    bool UIMouseEventArgs::IsLeftButtonPressed() const
    {
        return isLeftButtonPressed;
    }

    bool UIMouseEventArgs::IsRightButtonPressed() const
    {
        return isRightButtonPressed;
    }

    bool UIMouseEventArgs::IsMiddleButtonPressed() const
    {
        return isMiddleButtonPressed;
    }
}

#endif