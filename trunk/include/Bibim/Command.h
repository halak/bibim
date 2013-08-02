#pragma once
#ifndef __BIBIM_COMMAND_H__
#define __BIBIM_COMMAND_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>

    namespace Bibim
    {
        class Command : public SharedObject
        {
            public:
                virtual ~Command();

                virtual void Execute() = 0;

                virtual bool IsRestorable() const;

            protected:
                Command();
        };
    }

#endif