#pragma once
#ifndef __BIBIM_USHORTEVALUABLE_INTERFACE__
#define __BIBIM_USHORTEVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class IUShortEvaluable
        {
            public:
                virtual ~IUShortEvaluable() { }
                virtual ushort Evaluate() = 0;
        };
    }

#endif