#pragma once
#ifndef __BIBIM_UIEFFECT_H__
#define __BIBIM_UIEFFECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIElement.h>

    namespace Bibim
    {
        class UIEffect : public UIElement
        {
            BBAbstractObjectClass(UIEffect, UIElement);
            public:
                UIEffect();
                virtual ~UIEffect();

            private:
        };
    }

#   include <Bibim/UIEffect.inl>

#endif