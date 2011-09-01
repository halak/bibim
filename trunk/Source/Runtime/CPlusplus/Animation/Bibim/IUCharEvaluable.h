#pragma once
#ifndef __BIBIM_UCHAREVALUABLE_INTERFACE__
#define __BIBIM_UCHAREVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class IUCharEvaluable
        {
            public:
                virtual ~IUCharEvaluable() { }
                virtual uchar Evaluate() = 0;
        };
    }

#endif