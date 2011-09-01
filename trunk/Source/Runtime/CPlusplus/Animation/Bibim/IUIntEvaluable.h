#pragma once
#ifndef __BIBIM_UINTEVALUABLE_INTERFACE__
#define __BIBIM_UINTEVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class IUIntEvaluable
        {
            public:
                virtual ~IUIntEvaluable() { }
                virtual uint Evaluate() = 0;
        };
    }

#endif