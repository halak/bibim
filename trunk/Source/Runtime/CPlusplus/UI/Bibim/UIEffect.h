#pragma once
#ifndef __BIBIM_UIEFFECT_H__
#define __BIBIM_UIEFFECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIElement.h>

    namespace Bibim
    {
        class UIEffect : public UIElement
        {
            BBAbstractComponentClass(UIEffect, UIElement);
            public:
                enum Task
                {
                    TransformVertex = (1 << 0),
                    ShaderEffect = (1 << 1),
                };

            public:
                virtual ~UIEffect();

                inline int GetSlotIndex() const;

            protected:
                UIEffect(int slotIndex);

            private:
                int slotIndex;
        };
    }

#   include <Bibim/UIEffect.inl>

#endif