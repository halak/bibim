#pragma once
#ifndef __BIBIM_CHAREVALUABLE_INTERFACE__
#define __BIBIM_CHAREVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class ICharEvaluable
        {
            public:
                virtual ~ICharEvaluable() { }
                virtual char Evaulate() = 0;
        };
    }

#endif