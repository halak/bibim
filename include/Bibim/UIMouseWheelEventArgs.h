#pragma once
#ifndef __BIBIM_UIMOUSEWHEELEVENTARGS_H__
#define __BIBIM_UIMOUSEWHEELEVENTARGS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIMouseEventArgs.h>

    namespace Bibim
    {
        class UIMouseWheelEventArgs : public UIMouseEventArgs
        {
            public:
                UIMouseWheelEventArgs();
                UIMouseWheelEventArgs(UIMouseEventDispatcher* dispatcher, UIVisual* target, Point2 position, int wheelDelta);
                UIMouseWheelEventArgs(UIMouseEventDispatcher* dispatcher, UIVisual* target, Point2 position, bool isLeftButtonPressed, bool isRightButtonPressed, bool isMiddleButtonPressed, int wheelDelta);
                UIMouseWheelEventArgs(const UIMouseEventArgs& base, int wheelDelta);
                UIMouseWheelEventArgs(const UIMouseWheelEventArgs& original);
                virtual ~UIMouseWheelEventArgs();

                virtual UIMouseWheelEventArgs* Clone() const;

                virtual void Serialize(Serializer& context) const;

                inline int GetWheelDelta() const;

            private:
                int wheelDelta;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        int UIMouseWheelEventArgs::GetWheelDelta() const
        {
            return wheelDelta;
        }
    }

#endif