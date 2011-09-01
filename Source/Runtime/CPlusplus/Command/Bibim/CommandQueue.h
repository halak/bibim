#pragma once
#ifndef __BIBIM_COMMANDQUEUE_H__
#define __BIBIM_COMMANDQUEUE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>

    namespace Bibim
    {
        class CommandQueue : public GameComponent
        {
            BBClassFOURCC('C', 'M', 'D', 'Q');
            public:
                CommandQueue();
                virtual ~CommandQueue();               

            private:
                friend void __Startup__();
                static void __Startup__();
        };
    }

#endif