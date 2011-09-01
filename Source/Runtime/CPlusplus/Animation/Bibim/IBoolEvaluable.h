#pragma once
#ifndef __BIBIM_BOOLEVALUABLE_INTERFACE__
#define __BIBIM_BOOLEVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class IBoolEvaluable
        {
            public:
                virtual ~IBoolEvaluable() { }
                virtual bool Evaulate() = 0;
        };
    }

#endif