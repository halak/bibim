﻿#pragma once
#ifndef __BIBIM_UIDRAWINGCONTEXT_H__
#define __BIBIM_UIDRAWINGCONTEXT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIVisualVisitor.h>
#   include <Bibim/Vector2.h>

    namespace Bibim
    {
        class UIDrawingContext : public UIVisualVisitor
        {
            public:
                UIDrawingContext(UIRenderer* renderer);
                virtual ~UIDrawingContext();

                void Draw(UIVisual* target);

                inline void Draw(Image* image);
                inline void Draw(Image* image, bool horizontalFlip, bool verticalFlip);
                void Draw(const RectF& bounds, const RectF& clippedBounds, Image* image, bool horizontalFlip, bool verticalFlip);
                void Draw(Shape2D* shape, Color color);
                void DrawUnclipped(Vector2 position, Texture2D* texture);
                void DrawUnclipped(Vector2 position, float rotation, Image* image);
                void DrawUnclipped(Vector2 position, float rotation, Image* image, Color color);
                void DrawUnclipped(Vector2 position, float rotation, float scale, Image* image, Color color);
                void DrawUnclipped(Vector2 position, float rotation, Vector3 rotationAxis, float scale, Image* image, Color color);

                inline void DrawString(Vector2 position, Font* font, const String& text);
                inline void DrawString(Vector2 position, const FontString& fontString);
                inline void DrawString(const FontString& fontString);
                void DrawString(RectF bounds, Font* font, const String& text);
                void DrawString(const RectF& bounds, const RectF& clippedBounds, const FontString& fontString);

                void DrawLine(Vector2 p0, Vector2 p1, Color color);
                void DrawLines(int count, Vector2* p, Color color);
                void DrawRect(const RectF& bounds, Color color);
                void DrawCircle(Vector2 center, float radius, Color color);
                void DrawEllipse(const RectF& bounds, Color color);
                void DrawEllipse(Vector2 center, float xRadius, float yRadius, Color color);
                void DrawRoundedRect(RectF bounds, float radius, Color color);
                void DrawRoundedRect(RectF bounds, float leftTopRadius, float rightTopRadius, float leftBottomRadius, float rightBottomRadius, Color color);

                void DrawDebugLine(Vector2 p0, Vector2 p1, Color color);
                void DrawDebugLines(int count, Vector2* p, Color color);
                void DrawDebugRect(const RectF& bounds, Color color);

                void FillRect(const RectF& bounds, Color color);
                void FillCircle(Vector2 center, float radius, Color color);
                void FillEllipse(const RectF& bounds, Color color);
                void FillEllipse(Vector2 center, float xRadius, float yRadius, Color color);
                void FillRoundedRect(RectF bounds, float radius, Color color);
                void FillRoundedRect(RectF bounds, float leftTopRadius, float rightTopRadius, float leftBottomRadius, float rightBottomRadius, Color color);
                void FillTriangles(int count, Vector2* p, Color color);

                inline UIRenderer* GetRenderer() const;

            private:
                void Draw(const RectF& bounds, const RectF& clippedBounds, Image* image, Image* maskImage, bool horizontalFlip, bool verticalFlip);

            protected:
                inline void DrawChild(UIVisual* target);

                inline Vector2 GetOrigin() const;

                virtual void OnBegan();
                virtual void OnEnded();
                virtual void OnVisit();

            private:
                UIRenderer* renderer;
                UIEffectStackPtr effectStack;
                UIGeometryEffectPtr currentGeomEffect;
                ImagePtr currentMask;
                bool isDrawing;

                friend class UIPanel;
        };
    }

#   include <Bibim/UIDrawingContext.inl>

#endif