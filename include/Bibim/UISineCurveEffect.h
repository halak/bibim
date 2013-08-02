#pragma once
#ifndef __BIBIM_UISINECURVEEFFECT_H__
#define __BIBIM_UISINECURVEEFFECT_H__

#include <Bibim/FWD.h>
#include <Bibim/UIGeometryEffect.h>

#undef SetForm

namespace Bibim
{
    class UISineCurveEffect : public UIGeometryEffect
    {
        BBComponentClass(UISineCurveEffect, UIGeometryEffect, 'U', 'S', 'N', 'F');
        public:
            enum Form
            {
                VerticalWave,
                VerticalPot,
                Left,
                Right,
                HorizontalWave,
                HorizontalPot,
                Top,
                Bottom,
            };

        public:
            UISineCurveEffect();
            virtual ~UISineCurveEffect();

            inline float GetAmplitude() const;
            void SetAmplitude(float value);

            inline float GetOffset() const;
            void SetOffset(float value);

            inline float GetLength() const;
            void SetLength(float value);

            inline Form GetForm() const;
            void SetForm(Form value);

            virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color color);
            virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color color, Vector2* uv,  Texture2D* texture);
            virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color color, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2);

            virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color color, RectF clippingRect, Texture2D* texture);
            virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color color, RectF clippingRect, Texture2D* texture1, Vector2* uv2, Texture2D* texture2);

            virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color* c);
            virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color* c, Vector2* uv,  Texture2D* texture);
            virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color* c, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2);

            virtual void DrawQuad(UIRenderer* renderer, Vector3* p, Color color);
            virtual void DrawQuad(UIRenderer* renderer, Vector3* p, Color color, Vector2* uv,  Texture2D* texture);
            virtual void DrawQuad(UIRenderer* renderer, Vector3* p, Color color, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2);

        public:
            static Form ConvertFromStringToForm(const char* value);
            static const char* ConvertFromFormToString(Form value);

        private:
            float amplitude;
            float offset;
            float length;
            Form form;

            float startAxisWeight;
            float endAxisWeight;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    float UISineCurveEffect::GetAmplitude() const
    {
        return amplitude;
    }

    float UISineCurveEffect::GetOffset() const
    {
        return offset;
    }

    float UISineCurveEffect::GetLength() const
    {
        return length;
    }

    UISineCurveEffect::Form UISineCurveEffect::GetForm() const
    {
        return form;
    }
}

BBBindLuaEnum(Bibim::UISineCurveEffect::Form,
              Bibim::UISineCurveEffect::ConvertFromStringToForm,
              Bibim::UISineCurveEffect::ConvertFromFormToString);

#endif