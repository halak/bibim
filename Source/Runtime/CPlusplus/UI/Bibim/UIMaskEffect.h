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
                virtual ~UIMaskEffect();

            protected:
                UIMaskEffect(int slotIndex);

            private:
        };
    }

#   include <Bibim/UIMaskEffect.inl>

#endif