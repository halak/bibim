#pragma once
#ifndef __BIBIM_SPRITEEVALUABLE_INTERFACE__
#define __BIBIM_SPRITEEVALUABLE_INTERFACE__

#   include <Bibim/FWD.h>
#   include <Bibim/Sprite.h>

    namespace Bibim
    {
        class ISpriteEvaluable
        {
            public:
                virtual ~ISpriteEvaluable() { }
                virtual Sprite Evaluate() = 0;
        };
    }

#endif