#pragma once
#ifndef __BIBIM_UIMOUSEEVENTARGS_H__
#define __BIBIM_UIMOUSEEVENTARGS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIEventArgs.h>
#   include <Bibim/Point2.h>
#   include <Bibim/Rect.h>

    namespace Bibim
    {
        class UIMouseEventArgs : public UIEventArgs
        {
            public:
                UIMouseEventArgs();
                explicit UIMouseEventArgs(UIVisual* target);
                UIMouseEventArgs(UIVisual* target, Point2 position);
                UIMouseEventArgs(UIVisual* target, Point2 position, bool isLeftButtonPressed, bool isRightButtonPressed, bool isMiddleButtonPressed);
                UIMouseEventArgs(const UIMouseEventArgs& original);
                virtual ~UIMouseEventArgs();

                virtual UIMouseEventArgs* Clone() const;

                virtual void Serialize(Serializer& context) const;

                inline Point2 GetPosition() const;
                inline int GetPositionX() const;
                inline int GetPositionY() const;
                inline bool IsLeftButtonPressed() const;
                inline bool IsRightButtonPressed() const;
                inline bool IsMiddleButtonPressed() const;

            private:
                Point2 position;
                bool isLeftButtonPressed;
                bool isRightButtonPressed;
                bool isMiddleButtonPressed;
        };
    }

#   include <Bibim/UIMouseEventArgs.inl>

#endif