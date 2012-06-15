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
            protected: virtual void to_lua(lua_State *L) { type2lua(L, this); }
            public:
                UIKeyboardEventArgs();
                UIKeyboardEventArgs(UIVisual* target, Key::Code keyCode);
                UIKeyboardEventArgs(UIVisual* target, Key::Code keyCode0, Key::Code keyCode1, Key::Code keyCode2, Key::Code keyCode3);
                UIKeyboardEventArgs(const UIKeyboardEventArgs& original);
                virtual ~UIKeyboardEventArgs();

                virtual UIKeyboardEventArgs* Clone() const;

                inline bool Contains(Key::Code keyCode) const;
                inline Key::Code GetKeyCode0() const;
                inline Key::Code GetKeyCode1() const;
                inline Key::Code GetKeyCode2() const;
                inline Key::Code GetKeyCode3() const;
                inline Key::Code GetKeyCodeAt(int index) const;

                inline bool ContainsByChars(const char* keyCode) const;
                inline const char* GetKeyCode0AsChars() const;
                inline const char* GetKeyCode1AsChars() const;
                inline const char* GetKeyCode2AsChars() const;
                inline const char* GetKeyCode3AsChars() const;
                inline const char* GetKeyCodeAtAsChars(int index) const;

            private:
                Key::Code keyCode0;
                Key::Code keyCode1;
                Key::Code keyCode2;
                Key::Code keyCode3;
        };
    }

#   include <Bibim/UIKeyboardEventArgs.inl>

#endif