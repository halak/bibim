#pragma once
#ifndef __BIBIM_VECTOR4EVALUABLE_INTERFACE__
#define __BIBIM_VECTOR4EVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>
#   include <Bibim/Vector4.h>

    namespace Bibim
    {
        class IVector4Evaluable
        {
            public:
                virtual ~IVector4Evaluable() { }
                virtual Vector4 Evaluate() = 0;
        };
    }

#endif