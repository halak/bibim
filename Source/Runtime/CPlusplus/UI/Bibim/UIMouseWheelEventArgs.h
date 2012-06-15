#pragma once
#ifndef __BIBIM_UIMOUSEWHEELEVENTARGS_H__
#define __BIBIM_UIMOUSEWHEELEVENTARGS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIMouseEventArgs.h>

    namespace Bibim
    {
        class UIMouseWheelEventArgs : public UIMouseEventArgs
        {
            protected: virtual void to_lua(lua_State *L) { type2lua(L, this); }
            public:
                UIMouseWheelEventArgs();
                UIMouseWheelEventArgs(UIVisual* target, Point2 position, int wheelDelta);
                UIMouseWheelEventArgs(UIVisual* target, Point2 position, bool isLeftButtonPressed, bool isRightButtonPressed, bool isMiddleButtonPressed, int wheelDelta);
                UIMouseWheelEventArgs(const UIMouseEventArgs& base, int wheelDelta);
                UIMouseWheelEventArgs(const UIMouseWheelEventArgs& original);
                virtual ~UIMouseWheelEventArgs();

                virtual UIMouseWheelEventArgs* Clone() const;

                inline int GetWheelDelta() const;

            private:
                int wheelDelta;
        };
    }

#   include <Bibim/UIMouseWheelEventArgs.inl>

#endif