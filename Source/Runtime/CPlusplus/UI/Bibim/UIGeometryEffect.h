#pragma once
#ifndef __BIBIM_UIGEOMETRYEFFECT_H__
#define __BIBIM_UIGEOMETRYEFFECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIElement.h>

    namespace Bibim
    {
        class UIGeometryEffect : public UIElement
        {
            BBAbstractComponentClass(UIGeometryEffect, UIElement);
            public:
                virtual ~UIGeometryEffect();

            protected:
                UIGeometryEffect();
        };
    }

#   include <Bibim/UIGeometryEffect.inl>

#endif