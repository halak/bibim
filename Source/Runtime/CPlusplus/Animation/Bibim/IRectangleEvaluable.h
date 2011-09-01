#pragma once
#ifndef __BIBIM_RECTANGLEEVALUABLE_INTERFACE__
#define __BIBIM_RECTANGLEEVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class IRectangleEvaluable
        {
            public:
                virtual ~IRectangleEvaluable() { }
                virtual Rectangle Evaluate() = 0;
        };
    }

#endif