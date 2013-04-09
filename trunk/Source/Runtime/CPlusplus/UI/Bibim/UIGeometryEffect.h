#pragma once
#ifndef __BIBIM_UIGEOMETRYEFFECT_H__
#define __BIBIM_UIGEOMETRYEFFECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIElement.h>

    namespace Bibim
    {
        class UIGeometryEffect : public UIElement
        {
            BBAbstractComponentClass(UIGeometryEffect, UIElement);
            public:
                virtual ~UIGeometryEffect();

                inline virtual void BeginDraw(UIDrawingContext& context, UIVisual* visual);
                inline virtual void EndDraw(UIDrawingContext& context, UIVisual* visual);

                inline virtual void DrawLines(UIRenderer* renderer, int count, Vector2* p, Color color);
                inline virtual void DrawLines(UIRenderer* renderer, int count, Vector2* p, Color* c);

                inline virtual void DrawDebugLines(UIRenderer* renderer, int count, Vector2* p, Color color);
                inline virtual void DrawDebugLines(UIRenderer* renderer, int count, Vector2* p, Color* c);

                inline virtual void DrawTriangles(UIRenderer* renderer, int count, Vector2* p, Color color);

                inline virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color color);
                inline virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color color, Vector2* uv,  Texture2D* texture);
                inline virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color color, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2);

                inline virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color color, RectF clippingRect, Texture2D* texture);
                inline virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color color, RectF clippingRect, Texture2D* texture1, Vector2* uv2, Texture2D* texture2);

                inline virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color* c);
                inline virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color* c, Vector2* uv,  Texture2D* texture);
                inline virtual void DrawQuad(UIRenderer* renderer, Vector2* p, Color* c, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2);

                inline virtual void DrawQuad(UIRenderer* renderer, Vector3* p, Color color);
                inline virtual void DrawQuad(UIRenderer* renderer, Vector3* p, Color color, Vector2* uv,  Texture2D* texture);
                inline virtual void DrawQuad(UIRenderer* renderer, Vector3* p, Color color, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2);

            protected:
                UIGeometryEffect();
        };
    }

#   include <Bibim/UIGeometryEffect.inl>

    BBBindLua(Bibim::UIGeometryEffect);

#endif