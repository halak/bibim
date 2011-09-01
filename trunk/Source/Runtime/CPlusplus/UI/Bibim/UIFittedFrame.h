#pragma once
#ifndef __BIBIM_UIFITTEDFRAME_H__
#define __BIBIM_UIFITTEDFRAME_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIFrame.h>

    namespace Bibim
    {
        class UIFittedFrame : public UIFrame
        {
            public:
                static UIFittedFramePtr Instance;

            public:
                UIFittedFrame();
                virtual ~UIFittedFrame();

                virtual bool Setup(const RectangleF& bounds, const RectangleF& referenceBounds);
                virtual RectangleF ComputeBounds(UIVisualVisitor& visitor, Vector2 desiredSize);
        };
    }

#   include <Bibim/UIFittedFrame.inl>

#endif