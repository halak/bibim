#pragma once
#ifndef __BIBIM_COMMAND_H__
#define __BIBIM_COMMAND_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class Command
        {
            public:
                virtual ~Command();

                virtual void Execute() = 0;

                virtual bool IsRestorable() const;

            protected:
                Command();

            private:
                friend void __Startup__();
                static void __Startup__();
        };
    }

#endif