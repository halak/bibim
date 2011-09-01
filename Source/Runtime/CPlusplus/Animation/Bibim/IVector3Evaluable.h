#pragma once
#ifndef __BIBIM_VECTOR3EVALUABLE_INTERFACE__
#define __BIBIM_VECTOR3EVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>
#   include <Bibim/Vector3.h>

    namespace Bibim
    {
        class IVector3Evaluable
        {
            public:
                virtual ~IVector3Evaluable() { }
                virtual Vector3 Evaluate() = 0;
        };
    }

#endif