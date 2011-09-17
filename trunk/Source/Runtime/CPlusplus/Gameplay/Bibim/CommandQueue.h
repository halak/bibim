#pragma once
#ifndef __BIBIM_COMMANDQUEUE_H__
#define __BIBIM_COMMANDQUEUE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>

    namespace Bibim
    {
        class CommandQueue : public GameModule
        {
            BBGameModuleClass('C', 'M', 'D', 'Q');
            public:
                CommandQueue();
                virtual ~CommandQueue();
        };
    }

#   include <Bibim/CommandQueue.inl>

#endif