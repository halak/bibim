#pragma once
#ifndef __BIBIM_QUATERNIONEVALUABLE_INTERFACE__
#define __BIBIM_QUATERNIONEVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class IQuaternionEvaluable
        {
            public:
                virtual ~IQuaternionEvaluable() { }
                virtual Quaternion Evaluate() = 0;
        };
    }

#endif