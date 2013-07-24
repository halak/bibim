#pragma once
#ifndef __BIBIM_UIEVENTDISPATCHER_H__
#define __BIBIM_UIEVENTDISPATCHER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>

    namespace Bibim
    {
        class UIEventDispatcher : public GameModule
        {
            BBAbstractModuleClass(UIEventDispatcher, GameModule);
            public:
                UIEventDispatcher();
                virtual ~UIEventDispatcher();

            private:
        };
    }

#endif