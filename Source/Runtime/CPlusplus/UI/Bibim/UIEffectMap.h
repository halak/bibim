#pragma once
#ifndef __BIBIM_UIEFFECTMAP_H__
#define __BIBIM_UIEFFECTMAP_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIElement.h>

    namespace Bibim
    {
        class UIEffectMap : public UIElement
        {
            BBCreatableObjectClass(UIEffectMap, UIElement, UIElement, 'U', 'F', 'X', 'M');
            public:
                UIEffectMap();
                virtual ~UIEffectMap();

            private:
        };
    }

#   include <Bibim/UIEffectMap.inl>

#endif