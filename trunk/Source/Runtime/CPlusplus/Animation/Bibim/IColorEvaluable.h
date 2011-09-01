#pragma once
#ifndef __BIBIM_COLOREVALUABLE_INTERFACE__
#define __BIBIM_COLOREVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>
#   include <Bibim/Color.h>

    namespace Bibim
    {
        class IColorEvaluable
        {
            public:
                virtual ~IColorEvaluable() { }
                virtual Color Evaulate() = 0;
        };
    }

#endif