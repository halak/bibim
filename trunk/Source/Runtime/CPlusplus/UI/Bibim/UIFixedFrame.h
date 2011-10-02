#pragma once
#ifndef __BIBIM_UIFIXEDFRAME_H__
#define __BIBIM_UIFIXEDFRAME_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIFrame.h>

    namespace Bibim
    {
        class UIFixedFrame : public UIFrame
        {
            BBReadableObjectClass(UIFixedFrame, UIFrame, UIElement, 'U', 'F', 'X', 'F');
            public:
                UIFixedFrame();
                explicit UIFixedFrame(const RectF& Rect);
                virtual ~UIFixedFrame();

                virtual bool Setup(const RectF& bounds, const RectF& referenceBounds);
                virtual RectF ComputeBounds(UIVisualVisitor& visitor, Vector2 desiredSize);

                virtual void Move(Vector2 displacement);
                virtual bool IsMovable() const;

                virtual void Resize(float left, float top, float right, float bottom);
                virtual void ResizeTo(Vector2 size);
                virtual bool IsResizable() const;

                inline const RectF& GetRect() const;
                inline void SetRect(const RectF& value);

            private:
                RectF Rect;
        };
    }

#   include <Bibim/UIFixedFrame.inl>

#endif