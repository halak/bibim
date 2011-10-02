#pragma once
#ifndef __BIBIM_UIMOUSEEVENTARGS_H__
#define __BIBIM_UIMOUSEEVENTARGS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIEventArgs.h>
#   include <Bibim/Point.h>

    namespace Bibim
    {
        class UIMouseEventArgs : public UIEventArgs
        {
            BBObjectClass(UIMouseEventArgs, UIEventArgs, 'U', 'M', 'S', 'E');
            public:
                UIMouseEventArgs();
                UIMouseEventArgs(UIVisual* target, Point position);
                UIMouseEventArgs(UIVisual* target, Point position, bool isLeftButtonPressed, bool isRightButtonPressed, bool isMiddleButtonPressed);
                UIMouseEventArgs(const UIMouseEventArgs& original);
                virtual ~UIMouseEventArgs();

                virtual UIMouseEventArgs* Clone() const;

                inline Point GetPosition() const;
                inline bool IsLeftButtonPressed() const;
                inline bool IsRightButtonPressed() const;
                inline bool IsMiddleButtonPressed() const;

            private:
                Point position;
                bool isLeftButtonPressed;
                bool isRightButtonPressed;
                bool isMiddleButtonPressed;
        };
    }

#   include <Bibim/UIMouseEventArgs.inl>

#endif