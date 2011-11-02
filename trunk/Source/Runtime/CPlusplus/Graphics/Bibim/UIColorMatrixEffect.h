#pragma once
#ifndef __BIBIM_UICOLORMATRIXEFFECT_H__
#define __BIBIM_UICOLORMATRIXEFFECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIPixelEffect.h>
#   include <Bibim/Vector4.h>

    namespace Bibim
    {
        class UIColorMatrixEffect : public UIPixelEffect
        {
            BBComponentClass(UIColorMatrixEffect, UIPixelEffect, 'U', 'C', 'M', 'F');
            public:
                static const int ClassIndex = 0;

                class Effector : public UIRenderer::Effector
                {
                    public:
                        Effector(Effector* parent, UIColorMatrixEffect* effect);
                        virtual ~Effector();

                        virtual void Setup(ShaderEffect* effect);

                    private:
                        Vector4 red;
                        Vector4 green;
                        Vector4 blue;
                };

            public:
                UIColorMatrixEffect();
                UIColorMatrixEffect(Vector4 red, Vector4 green, Vector4 blue);
                virtual ~UIColorMatrixEffect();

                virtual Effector* CreateEffector(UIRenderer::Effector* parent);

                inline Vector4 GetRed() const;
                inline void SetRed(Vector4 value);

                inline Vector4 GetGreen() const;
                inline void SetGreen(Vector4 value);

                inline Vector4 GetBlue() const;
                inline void SetBlue(Vector4 value);

                inline Vector4 GetAlpha() const;
                inline void SetAlpha(Vector4 value);

            public:
                static const Vector4 DefaultRed;
                static const Vector4 DefaultGreen;
                static const Vector4 DefaultBlue;

            private:
                Vector4 red;
                Vector4 green;
                Vector4 blue;
        };
    }

#   include <Bibim/UIColorMatrixEffect.inl>

#endif