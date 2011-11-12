#pragma once
#ifndef __BIBIM_UPDATEABLE_INTERFACE__
#define __BIBIM_UPDATEABLE_INTERFACE__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class IUpdateable
        {
            public:
                virtual ~IUpdateable() { }

                virtual void Update(float dt, int timestamp) = 0;
        };
    }

#endif