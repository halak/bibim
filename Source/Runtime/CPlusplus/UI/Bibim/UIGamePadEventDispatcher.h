#pragma once
#ifndef __BIBIM_UIGAMEPADEVENTDISPATCHER_H__
#define __BIBIM_UIGAMEPADEVENTDISPATCHER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIEventDispatcher.h>

    namespace Bibim
    {
        class UIGamePadEventDispatcher : public UIEventDispatcher
        {
            BBGameModuleClass('U', 'I', 'G', 'P');
            public:
                UIGamePadEventDispatcher();
                virtual ~UIGamePadEventDispatcher();

            private:
        };
    }

#   include <Bibim/UIGamePadEventDispatcher.inl>

#endif