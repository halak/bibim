#pragma once
#ifndef __BIBIM_UITINTEFFECT_H__
#define __BIBIM_UITINTEFFECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIEffect.h>

    namespace Bibim
    {
        class UITintEffect : public UIEffect
        {
            BBCreatableObjectClass(UITintEffect, UIEffect, UIElement, 'U', 'T', 'N', 'F');
            public:
                UITintEffect();
                virtual ~UITintEffect();

            private:
        };
    }

#   include <Bibim/UITintEffect.inl>

#endif