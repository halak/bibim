#pragma once
#ifndef __BIBIM_UIALIGNEDFRAME_H__
#define __BIBIM_UIALIGNEDFRAME_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIFrame.h>
#   include <Bibim/Vector2.h>

    namespace Bibim
    {
        class UIAlignedFrame : public UIFrame
        {
            public:
                enum Alignment
                {
                    LeftTop,
                    LeftBottom,
                    LeftMiddle,
                    RightTop,
                    RightBottom,
                    RightMiddle,
                    CenterTop,
                    CenterBottom,
                    Center,
                };

            public:
                UIAlignedFrame();
                UIAlignedFrame(Vector2 offset, Vector2 size);
                UIAlignedFrame(Alignment align, Vector2 offset, Vector2 size);
                virtual ~UIAlignedFrame();

                virtual bool Setup(const RectF& bounds, const RectF& referenceBounds);
                virtual RectF ComputeBounds(UIVisualVisitor& visitor, Vector2 desiredSize);

                virtual void Move(Vector2 displacement);
                virtual bool IsMovable() const;

                virtual void Resize(float left, float top, float right, float bottom);
                virtual void ResizeTo(Vector2 size);
                virtual bool IsResizable() const;

                inline Alignment GetAlign() const;
                void SetAlign(Alignment value);
                
                inline Vector2 GetOffset() const;
                void SetOffset(Vector2 value);

                inline Vector2 GetSize() const;
                void SetSize(Vector2 value);

            private:
                Alignment align;
                Vector2 offset;
                Vector2 size;
                RectF lastBounds;
                RectF lastReferenceBounds;
                Vector2 lastDesiredSize;
                bool boundsChanged;
        };
    }

#   include <Bibim/UIAlignedFrame.inl>

#endif