#pragma once
#ifndef __BIBIM_UIPIXELEFFECT_H__
#define __BIBIM_UIPIXELEFFECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIElement.h>
#   include <Bibim/UIRenderer.h>

    namespace Bibim
    {
        class UIPixelEffect : public UIElement
        {
            BBAbstractComponentClass(UIPixelEffect, UIElement);
            public:
                virtual ~UIPixelEffect();

                virtual UIRenderer::Effector* CreateEffector(UIRenderer::Effector* /*parent*/, bool /*isShaderFunctionRendering*/) { return 0; }

                inline int GetSlotIndex() const;
                inline bool IsFixedFunctionImplemented() const;
                inline bool IsShaderFunctionImplemented() const;

            protected:
                UIPixelEffect(int slotIndex, bool isFixedFunctionImplemented, bool isShaderFunctionImplemented);

            private:
                int slotIndex;
                bool isFixedFunctionImplemented;
                bool isShaderFunctionImplemented;
                bool reserved[2];
        };
    }

#   include <Bibim/UIPixelEffect.inl>

#endif