#pragma once
#ifndef __BIBIM_UITINTEFFECT_H__
#define __BIBIM_UITINTEFFECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIGeometryEffect.h>
#   include <Bibim/Vector4.h>

    namespace Bibim
    {
        class UITintEffect : public UIGeometryEffect
        {
            BBComponentClass(UITintEffect, UIGeometryEffect, 'U', 'T', 'N', 'F');
            public:
                static const int ClassIndex = 0;

            public:
                UITintEffect();
                UITintEffect(Vector4 value);
                virtual ~UITintEffect();

                inline Vector4 GetValue() const;
                inline void SetValue(Vector4 value);

            private:
                Vector4 value;
        };
    }

#   include <Bibim/UITintEffect.inl>

#endif