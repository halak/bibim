#pragma once
#ifndef __BIBIM_UIGAMEPADEVENTARGS_H__
#define __BIBIM_UIGAMEPADEVENTARGS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIEventArgs.h>

    namespace Bibim
    {
        class UIGamePadEventArgs : public UIEventArgs
        {
            protected: virtual void to_lua(lua_State *L) { type2lua(L, this); }
            public:
                UIGamePadEventArgs();
                virtual ~UIGamePadEventArgs();

            private:
        };
    }

#   include <Bibim/UIGamePadEventArgs.inl>

#endif