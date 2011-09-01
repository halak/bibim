#pragma once
#ifndef __BIBIM_UIFIXEDFRAME_H__
#define __BIBIM_UIFIXEDFRAME_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIFrame.h>

    namespace Bibim
    {
        class UIFixedFrame : public UIFrame
        {
            public:
                UIFixedFrame();
                explicit UIFixedFrame(const RectangleF& rectangle);
                virtual ~UIFixedFrame();

                virtual bool Setup(const RectangleF& bounds, const RectangleF& referenceBounds);
                virtual RectangleF ComputeBounds(UIVisualVisitor& visitor, Vector2 desiredSize);

                virtual void Move(Vector2 displacement);
                virtual bool IsMovable() const;

                virtual void Resize(float left, float top, float right, float bottom);
                virtual void ResizeTo(Vector2 size);
                virtual bool IsResizable() const;

                inline const RectangleF& GetRectangle() const;
                inline void SetRectangle(const RectangleF& value);

            private:
                RectangleF rectangle;
        };
    }

#   include <Bibim/UIFixedFrame.inl>

#endif