#pragma once
#ifndef __BIBIM_UICOLORMATRIXEFFECT_H__
#define __BIBIM_UICOLORMATRIXEFFECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIEffect.h>
#   include <Bibim/Vector4.h>

    namespace Bibim
    {
        class UIColorMatrixEffect : public UIEffect
        {
            BBComponentClass(UIColorMatrixEffect, UIEffect, 'U', 'C', 'M', 'F');
            public:
                static const int ClassIndex = 2;

            public:
                UIColorMatrixEffect();
                UIColorMatrixEffect(Vector4 red, Vector4 green, Vector4 blue, Vector4 alpha);
                virtual ~UIColorMatrixEffect();

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
                static const Vector4 DefaultAlpha;

            private:
                Vector4 red;
                Vector4 green;
                Vector4 blue;
                Vector4 alpha;
        };
    }

#   include <Bibim/UIColorMatrixEffect.inl>

#endif