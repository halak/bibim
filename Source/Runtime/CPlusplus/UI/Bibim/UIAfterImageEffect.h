#pragma once
#ifndef __BIBIM_UIAFTERIMAGEEFFECT_H__
#define __BIBIM_UIAFTERIMAGEEFFECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIGeometryEffect.h>
#   include <Bibim/Matrix4.h>
#   include <deque>
#   include <map>

    namespace Bibim
    {
        class UIAfterImageEffect : public UIGeometryEffect
        {
            BBComponentClass(UIAfterImageEffect, UIGeometryEffect, 'U', 'A', 'I', 'F');
            public:
                static const int ClassIndex = 1;

            public:
                UIAfterImageEffect();
                virtual ~UIAfterImageEffect();

                inline int GetSkippedFrames() const;
                void SetSkippedFrames(int value);

                inline int GetTotalFrames() const;
                void SetTotalFrames(int value);

                virtual void BeginDraw(UIDrawingContext& context, UIVisual* visual);
                virtual void EndDraw(UIDrawingContext& context, UIVisual* visual);

                virtual void DrawLines(UIRenderer* renderer, int count, Vector2* p, Color color);
                virtual void DrawLines(UIRenderer* renderer, int count, Vector2* p, Color* c);

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
                typedef std::deque<int> AICollection;
                typedef std::map<UIVisual*, AICollection*> AIDictionary;

            private:
                int skippedFrames;
                int totalFrames;

                AICollection* currentAfterImages;
                Matrix4 currentTransform;
                AIDictionary afterImages;
        };
    }

#   include <Bibim/UIAfterImageEffect.inl>

#endif