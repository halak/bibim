#pragma once
#ifndef __BIBIM_FLOATRANGEEVALUABLE_INTERFACE__
#define __BIBIM_FLOATRANGEEVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>
#   include <Bibim/Range.h>

    namespace Bibim
    {
        class IFloatRangeEvaluable
        {
            public:
                virtual ~IFloatRangeEvaluable() { }
                virtual FloatRange Evaluate() = 0;
        };
    }

#endif