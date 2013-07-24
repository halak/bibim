#pragma once
#ifndef __BIBIM_UIKEYBOARDEVENTARGS_H__
#define __BIBIM_UIKEYBOARDEVENTARGS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIEventArgs.h>
#   include <Bibim/Key.h>

    namespace Bibim
    {
        class UIKeyboardEventArgs : public UIEventArgs
        {
            public:
                UIKeyboardEventArgs();
                UIKeyboardEventArgs(UIKeyboardEventDispatcher* dispatcher, UIVisual* target, Key::Code keyCode);
                UIKeyboardEventArgs(UIKeyboardEventDispatcher* dispatcher, UIVisual* target, Key::Code keyCode0, Key::Code keyCode1, Key::Code keyCode2, Key::Code keyCode3);
                UIKeyboardEventArgs(const UIKeyboardEventArgs& original);
                virtual ~UIKeyboardEventArgs();

                virtual UIKeyboardEventArgs* Clone() const;

                virtual void Serialize(Serializer& context) const;

                inline UIKeyboardEventDispatcher* GetDispatcher() const;
                inline bool Contains(Key::Code keyCode) const;
                inline Key::Code GetKeyCode0() const;
                inline Key::Code GetKeyCode1() const;
                inline Key::Code GetKeyCode2() const;
                inline Key::Code GetKeyCode3() const;
                inline Key::Code GetKeyCodeAt(int index) const;

            private:
                UIKeyboardEventDispatcher* dispatcher;
                Key::Code keyCode0;
                Key::Code keyCode1;
                Key::Code keyCode2;
                Key::Code keyCode3;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        UIKeyboardEventDispatcher* UIKeyboardEventArgs::GetDispatcher() const
        {
            return dispatcher;
        }

        bool UIKeyboardEventArgs::Contains(Key::Code keyCode) const
        {
            return keyCode0 == keyCode ||
                   keyCode1 == keyCode ||
                   keyCode2 == keyCode ||
                   keyCode3 == keyCode;
        }

        Key::Code UIKeyboardEventArgs::GetKeyCode0() const
        {
            return keyCode0;
        }

        Key::Code UIKeyboardEventArgs::GetKeyCode1() const
        {
            return keyCode1;
        }

        Key::Code UIKeyboardEventArgs::GetKeyCode2() const
        {
            return keyCode2;
        }

        Key::Code UIKeyboardEventArgs::GetKeyCode3() const
        {
            return keyCode3;
        }

        Key::Code UIKeyboardEventArgs::GetKeyCodeAt(int index) const
        {
            switch (index)
            {
                case 0: return keyCode0;
                case 1: return keyCode1;
                case 2: return keyCode2;
                case 3: return keyCode3;
                default: return Key::None;
            }
        }
    }

#endif