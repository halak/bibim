#pragma once
#ifndef __BIBIM_UIDRAWINGCONTEXT_H__
#define __BIBIM_UIDRAWINGCONTEXT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIVisualVisitor.h>
#    include <Bibim/Vector2.h>

    namespace Bibim
    {
        class UIDrawingContext : public UIVisualVisitor
        {
            public:
                UIDrawingContext(UIRenderer* renderer);
                virtual ~UIDrawingContext();

                void Draw(UIVisual* target);

                inline void Draw(UIImage* image);
                inline void Draw(UIImage* image, bool horizontalFlip, bool verticalFlip);
                void Draw(const RectF& bounds, const RectF& clippedBounds, UIImage* image, bool horizontalFlip, bool verticalFlip);
                void Draw(Vector2 position, Texture2D* texture);

                inline void DrawString(Font* font, const String& text);
                inline void DrawString(const FontString& fontString);
                inline void DrawString(Vector2 position, Font* font, const String& text);
                void DrawString(const RectF& bounds, const RectF& clippedBounds, Font* font, const String& text);
                void DrawString(const RectF& bounds, const RectF& clippedBounds, const FontString& fontString);
                void DrawRect(const RectF& bounds, float width, Color color);

                void FillRect(const RectF& bounds, float width, Color color);

            protected:
                inline void DrawChild(UIVisual* target);

                virtual void OnBegan();
                virtual void OnEnded();
                virtual void OnVisit();               

            private:
                UIRenderer* renderer;
                bool isDrawing;

                friend class UIPanel;
        };
    }

#   include <Bibim/UIDrawingContext.inl>

#endif