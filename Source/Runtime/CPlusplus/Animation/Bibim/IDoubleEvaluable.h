#pragma once
#ifndef __BIBIM_DOUBLEEVALUABLE_INTERFACE__
#define __BIBIM_DOUBLEEVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class IDoubleEvaluable
        {
            public:
                virtual ~IDoubleEvaluable() { }
                virtual double Evaulate() = 0;
        };
    }

#endif