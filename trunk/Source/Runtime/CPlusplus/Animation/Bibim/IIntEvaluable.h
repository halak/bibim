#pragma once
#ifndef __BIBIM_INTEVALUABLE_INTERFACE__
#define __BIBIM_INTEVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class IIntEvaluable
        {
            public:
                virtual ~IIntEvaluable() { }
                virtual int Evaluate() = 0;
        };
    }

#endif