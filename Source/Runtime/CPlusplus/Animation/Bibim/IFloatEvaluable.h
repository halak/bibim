#pragma once
#ifndef __BIBIM_FLOATEVALUABLE_INTERFACE__
#define __BIBIM_FLOATEVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class IFloatEvaluable
        {
            public:
                virtual ~IFloatEvaluable() { }
                virtual float Evaluate() = 0;
        };
    }

#endif