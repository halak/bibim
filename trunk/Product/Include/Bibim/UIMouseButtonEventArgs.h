#pragma once
#ifndef __BIBIM_UIMOUSEBUTTONEVENTARGS_H__
#define __BIBIM_UIMOUSEBUTTONEVENTARGS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIMouseEventArgs.h>
#   include <Bibim/Key.h>

    namespace Bibim
    {
        class UIMouseButtonEventArgs : public UIMouseEventArgs
        {
            public:
                UIMouseButtonEventArgs();
                UIMouseButtonEventArgs(UIMouseEventDispatcher* dispatcher, UIVisual* target, Point2 position, Key::Code buttonCode);
                UIMouseButtonEventArgs(UIMouseEventDispatcher* dispatcher, UIVisual* target, Point2 position, bool isLeftButtonPressed, bool isRightButtonPressed, bool isMiddleButtonPressed, Key::Code buttonCode);
                UIMouseButtonEventArgs(const UIMouseEventArgs& base, Key::Code buttonCode);
                UIMouseButtonEventArgs(const UIMouseButtonEventArgs& original);
                virtual ~UIMouseButtonEventArgs();

                virtual UIMouseButtonEventArgs* Clone() const;

                virtual void Serialize(Serializer& context) const;

                inline Key::Code GetButtonCode() const;

            private:
                Key::Code buttonCode;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Key::Code UIMouseButtonEventArgs::GetButtonCode() const
        {
            return buttonCode;
        }
    }

#endif