#pragma once
#ifndef __BIBIM_UPDATEABLE_INTERFACE__
#define __BIBIM_UPDATEABLE_INTERFACE__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class IUpdateable
        {
            BBInterfaceFOURCC('I', 'U', 'D', 'T');
            public:
                virtual ~IUpdateable() { }

                virtual void Update(float dt, uint timestamp) = 0;
        };
    }

#endif