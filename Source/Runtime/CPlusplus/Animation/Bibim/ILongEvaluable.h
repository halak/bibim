#pragma once
#ifndef __BIBIM_LONGEVALUABLE_INTERFACE__
#define __BIBIM_LONGEVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class ILongEvaluable
        {
            public:
                virtual ~ILongEvaluable() { }
                virtual long Evaluate() = 0;
        };
    }

#endif