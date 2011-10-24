#pragma once
#ifndef __BIBIM_UIMASKEFFECT_H__
#define __BIBIM_UIMASKEFFECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIEffect.h>

    namespace Bibim
    {
        class UIMaskEffect : public UIEffect
        {
            BBAbstractComponentClass(UIMaskEffect, UIEffect);
            public:
                UIMaskEffect();
                virtual ~UIMaskEffect();

            private:
        };
    }

#   include <Bibim/UIMaskEffect.inl>

#endif