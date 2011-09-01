#pragma once
#ifndef __BIBIM_POINTEVALUABLE_INTERFACE__
#define __BIBIM_POINTEVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>
#   include <Bibim/Point.h>

    namespace Bibim
    {
        class IPointEvaluable
        {
            public:
                virtual ~IPointEvaluable() { }
                virtual Point Evaluate() = 0;
        };
    }

#endif