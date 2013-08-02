#pragma once
#ifndef __BIBIM_UIMASKEFFECT_H__
#define __BIBIM_UIMASKEFFECT_H__

#include <Bibim/FWD.h>
#include <Bibim/UIPixelEffect.h>

namespace Bibim
{
    class UIMaskEffect : public UIPixelEffect
    {
        BBAbstractComponentClass(UIMaskEffect, UIPixelEffect);
        public:
            static const int ClassIndex = 2;

            class MaskEffector : public UIRenderer::Effector
            {
                public:
                    MaskEffector(UIMaskEffect* effect);
                    MaskEffector(int shaderEffectNameHint, UIMaskEffect* effect);
                    virtual ~MaskEffector();

                    inline Image* GetMask() const;

                private:
                    Image* mask;
            };

        public:
            virtual ~UIMaskEffect();

            inline Image* GetMask() const;
            void SetMask(Image* value);

        protected:
            UIMaskEffect(bool isFixedFunctionImplemented, bool isShaderFunctionImplemented, Image* mask);

        private:
            ImagePtr mask;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Image* UIMaskEffect::MaskEffector::GetMask() const
    {
        return mask;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Image* UIMaskEffect::GetMask() const
    {
        return mask;
    }
}

#endif