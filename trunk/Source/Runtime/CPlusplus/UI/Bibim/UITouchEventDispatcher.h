#pragma once
#ifndef __BIBIM_UITOUCHEVENTDISPATCHER_H__
#define __BIBIM_UITOUCHEVENTDISPATCHER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>

    namespace Bibim
    {
        class UITouchEventDispatcher : public GameComponent
        {
            BBClassFOURCC('U', 'I', 'T', 'H');
            public:
                UITouchEventDispatcher();
                virtual ~UITouchEventDispatcher();

            private:
        };
    }

#   include <Bibim/UITouchEventDispatcher.inl>

#endif