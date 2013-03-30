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

            public:
                UIColorMatrixEffect();
                UIColorMatrixEffect(Vector4 red, Vector4 green, Vector4 blue);
                virtual ~UIColorMatrixEffect();

                virtual UIRenderer::Effector* CreateEffector(UIRenderer::Effector* parent, bool isShaderFunctionRendering);

                inline void Reset();
                inline void Grayscale(Vector4 value);
                inline void GrayscaleRGBA(float r, float g, float b, float a);
                inline void Tint(Vector3 value);
                inline void TintRGB(float r, float g, float b);
                inline void Fill(Vector3 value);
                inline void FillRGB(float r, float g, float b);

                inline Vector4 GetRed() const;
                inline void SetRed(Vector4 value);
                inline void SetRedRGBA(float r, float g, float b, float a);

                inline Vector4 GetGreen() const;
                inline void SetGreen(Vector4 value);
                inline void SetGreenRGBA(float r, float g, float b, float a);

                inline Vector4 GetBlue() const;
                inline void SetBlue(Vector4 value);
                inline void SetBlueRGBA(float r, float g, float b, float a);

            public:
                static const Vector4 DefaultRed;
                static const Vector4 DefaultGreen;
                static const Vector4 DefaultBlue;

            private:
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

            private:
                Vector4 red;
                Vector4 green;
                Vector4 blue;
        };
    }

#   include <Bibim/UIColorMatrixEffect.inl>

#endif