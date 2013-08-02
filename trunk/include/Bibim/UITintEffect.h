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
                UITintEffect();
                UITintEffect(Vector4 value);
                virtual ~UITintEffect();

                inline Vector4 GetValue() const;
                inline void SetValue(Vector4 value);
                inline void SetValueRGBA(float r, float g, float b, float a);

                virtual void DrawLines(UIRenderer* renderer, int count, Vector2* p, Color color);
                virtual void DrawLines(UIRenderer* renderer, int count, Vector2* p, Color* c);

                virtual void DrawDebugLines(UIRenderer* renderer, int count, Vector2* p, Color color);
                virtual void DrawDebugLines(UIRenderer* renderer, int count, Vector2* p, Color* c);

                virtual void DrawTriangles(UIRenderer* renderer, int count, Vector2* p, Color color);

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

            private:
                Vector4 value;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Vector4 UITintEffect::GetValue() const
        {
            return value;
        }

        void UITintEffect::SetValue(Vector4 value)
        {
            this->value = value;
        }

        void UITintEffect::SetValueRGBA(float r, float g, float b, float a)
        {
            SetValue(Vector4(r, g, b, a));
        }
    }

#endif