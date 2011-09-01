#pragma once
#ifndef __BIBIM_VECTOR2EVALUABLE_INTERFACE__
#define __BIBIM_VECTOR2EVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>
#   include <Bibim/Vector2.h>

    namespace Bibim
    {
        class IVector2Evaluable
        {
            public:
                virtual ~IVector2Evaluable() { }
                virtual Vector2 Evaluate() = 0;
        };
    }

#endif