#pragma once
#ifndef __BIBIM_UIANCHOREDFRAME_H__
#define __BIBIM_UIANCHOREDFRAME_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIFrame.h>

    namespace Bibim
    {
        class UIAnchoredFrame : public UIFrame
        {
            public:
                UIAnchoredFrame();
                virtual ~UIAnchoredFrame();

                virtual bool Setup(const RectangleF& bounds, const RectangleF& referenceBounds);
                virtual RectangleF ComputeBounds(UIVisualVisitor& visitor, Vector2 desiredSize);

            private:
        };
    }

#   include <Bibim/UIAnchoredFrame.inl>

#endif