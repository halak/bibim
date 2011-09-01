#pragma once
#ifndef __BIBIM_SHORTEVALUABLE_INTERFACE__
#define __BIBIM_SHORTEVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class IShortEvaluable
        {
            public:
                virtual ~IShortEvaluable() { }
                virtual short Evaluate() = 0;
        };
    }

#endif