#pragma once
#ifndef __BIBIM_UIOPACITYMASKEFFECT_H__
#define __BIBIM_UIOPACITYMASKEFFECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIMaskEffect.h>

    namespace Bibim
    {
        class UIOpacityMaskEffect : public UIMaskEffect
        {
            BBComponentClass(UIOpacityMaskEffect, UIMaskEffect, 'U', 'O', 'M', 'E');
            public:
                static const int ClassIndex = 1;

            public:
                UIOpacityMaskEffect();
                virtual ~UIOpacityMaskEffect();
        };
    }

#   include <Bibim/UIOpacityMaskEffect.inl>

#endif