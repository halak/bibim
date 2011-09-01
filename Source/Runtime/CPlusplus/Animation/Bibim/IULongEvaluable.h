#pragma once
#ifndef __BIBIM_ULONGEVALUABLE_INTERFACE__
#define __BIBIM_ULONGEVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class IULongEvaluable
        {
            public:
                virtual ~IULongEvaluable() { }
                virtual ulong Evaluate() = 0;
        };
    }

#endif