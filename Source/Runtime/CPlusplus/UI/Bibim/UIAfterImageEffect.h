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
                UIAfterImageEffect();
                virtual ~UIAfterImageEffect();

                inline int GetSkippedFrames() const;
                void SetSkippedFrames(int value);

                inline int GetTotalFrames() const;
                void SetTotalFrames(int value);

                inline bool GetActive() const;
                inline void SetActive(bool value);

                virtual void BeginDraw(UIDrawingContext& context, UIVisual* visual);
                virtual void EndDraw(UIDrawingContext& context, UIVisual* visual);

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
                struct Frame
                {
                    Matrix4 transform;
                    Vector2 positions[4];
                    Color color;
                    Vector2 uv[4];
                    Texture2DPtr texture;

                    Frame(const Matrix4& transform, Vector2* p4, Color c, Vector2* uv4, Texture2D* texture);
                    Frame(const Matrix4& transform, Vector2* p4, Color c, RectF clippingRect, Texture2D* texture);
                };

                struct AfterImage
                {
                    std::deque<Frame> Frames;
                    int SkippedFrames;
                };

                typedef std::map<UIVisual*, AfterImage*> AfterImageDictionary;

            private:
                inline byte GetOpacityDecrement() const;

            private:
                int skippedFrames;
                int totalFrames;
                bool active;

                AfterImage* currentAfterImage;
                Matrix4 currentTransform;
                AfterImageDictionary afterImages;
        };
    }

#endif