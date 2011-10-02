#pragma once
#ifndef __BIBIM_UIGAMEPADEVENTARGS_H__
#define __BIBIM_UIGAMEPADEVENTARGS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIEventArgs.h>

    namespace Bibim
    {
        class UIGamePadEventArgs : public UIEventArgs
        {
            BBObjectClass(UIGamePadEventArgs, UIEventArgs, 'U', 'G', 'P', 'E');
            public:
                UIGamePadEventArgs();
                virtual ~UIGamePadEventArgs();

            private:
        };
    }

#   include <Bibim/UIGamePadEventArgs.inl>

#endif