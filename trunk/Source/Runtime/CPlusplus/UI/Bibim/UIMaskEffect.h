#pragma once
#ifndef __BIBIM_UIMASKEFFECT_H__
#define __BIBIM_UIMASKEFFECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIPixelEffect.h>

    namespace Bibim
    {
        class UIMaskEffect : public UIPixelEffect
        {
            BBAbstractComponentClass(UIMaskEffect, UIPixelEffect);
            public:
                virtual ~UIMaskEffect();

                inline Image* GetMask() const;
                void SetMask(Image* value);

            protected:
                UIMaskEffect(int slotIndex, bool isFixedFunctionImplemented, bool isShaderFunctionImplemented);

            private:
                ImagePtr mask;
        };
    }

#   include <Bibim/UIMaskEffect.inl>

#endif