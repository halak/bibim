#pragma once
#ifndef __BIBIM_UICOLORMATRIXEFFECT_H__
#define __BIBIM_UICOLORMATRIXEFFECT_H__

#include <Bibim/FWD.h>
#include <Bibim/UIPixelEffect.h>
#include <Bibim/Vector4.h>

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

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    void UIColorMatrixEffect::Reset()
    {
        red = DefaultRed;
        green = DefaultGreen;
        blue = DefaultBlue;
    }

    void UIColorMatrixEffect::Grayscale(Vector4 value)
    {
        red = value;
        green = value;
        blue = value;
    }

    void UIColorMatrixEffect::GrayscaleRGBA(float r, float g, float b, float a)
    {
        red = Vector4(r, g, b, a);
        green = Vector4(r, g, b, a);
        blue = Vector4(r, g, b, a);
    }

    void UIColorMatrixEffect::Tint(Vector3 value)
    {
        red = Vector4(value.X, 0.0f, 0.0f, 0.0f);
        green = Vector4(0.0f, value.Y, 0.0f, 0.0f);
        blue = Vector4(0.0f, 0.0f, value.Z, 0.0f);
    }
    
    void UIColorMatrixEffect::TintRGB(float r, float g, float b)
    {
        Tint(Vector3(r, g, b));
    }

    void UIColorMatrixEffect::Fill(Vector3 value)
    {
        red = Vector4(0.0f, 0.0f, 0.0f, value.X);
        green = Vector4(0.0f, 0.0f, 0.0f, value.Y);
        blue = Vector4(0.0f, 0.0f, 0.0f, value.Z);
    }

    void UIColorMatrixEffect::FillRGB(float r, float g, float b)
    {
        Fill(Vector3(r, g, b));
    }

    Vector4 UIColorMatrixEffect::GetRed() const
    {
        return red;
    }

    void UIColorMatrixEffect::SetRed(Vector4 value)
    {
        red = value;
    }

    void UIColorMatrixEffect::SetRedRGBA(float r, float g, float b, float a)
    {
        red = Vector4(r, g, b, a);
    }

    Vector4 UIColorMatrixEffect::GetGreen() const
    {
        return green;
    }

    void UIColorMatrixEffect::SetGreen(Vector4 value)
    {
        green = value;
    }

    void UIColorMatrixEffect::SetGreenRGBA(float r, float g, float b, float a)
    {
        green = Vector4(r, g, b, a);
    }

    Vector4 UIColorMatrixEffect::GetBlue() const
    {
        return blue;
    }

    void UIColorMatrixEffect::SetBlue(Vector4 value)
    {
        blue = value;
    }

    void UIColorMatrixEffect::SetBlueRGBA(float r, float g, float b, float a)
    {
        blue = Vector4(r, g, b, a);
    }
}

#endif