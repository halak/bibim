#pragma once
#ifndef __BIBIM_UIFRAME_H__
#define __BIBIM_UIFRAME_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIElement.h>
#   include <Bibim/RectangleF.h>

    namespace Bibim
    {
        class UIFrame : public UIElement
        {
            public:
                UIFrame();
                virtual ~UIFrame();

                virtual bool Setup(const RectangleF& bounds, const RectangleF& referenceBounds) = 0;
                virtual RectangleF ComputeBounds(UIVisualVisitor& visitor, Vector2 desiredSize) = 0;

                virtual void Move(Vector2 displacement);
                virtual bool IsMovable() const;

                virtual void Resize(float left, float top, float right, float bottom);
                virtual void ResizeTo(Vector2 size);
                virtual bool IsResizable() const;
        };
    }

#   include <Bibim/UIFrame.inl>

#endif