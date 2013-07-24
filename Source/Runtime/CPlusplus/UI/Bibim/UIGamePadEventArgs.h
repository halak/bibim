#pragma once
#ifndef __BIBIM_UIGAMEPADEVENTARGS_H__
#define __BIBIM_UIGAMEPADEVENTARGS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIEventArgs.h>

    namespace Bibim
    {
        class UIGamePadEventArgs : public UIEventArgs
        {
            public:
                UIGamePadEventArgs();
                virtual ~UIGamePadEventArgs();

            private:
        };
    }

#endif