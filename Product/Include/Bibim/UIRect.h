#pragma once
#ifndef __BIBIM_UIRECT_H__
#define __BIBIM_UIRECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIShape.h>

    namespace Bibim
    {
        class UIRect : public UIShape
        {
            BBComponentClass(UIRect, UIShape, 'U', 'R', 'C', 'T');
            public:
                UIRect();
                virtual ~UIRect();

            protected:
                virtual void FillShape(UIDrawingContext& context, const RectF& clippedBounds, const RectF& bounds, Color color);
                virtual void DrawShape(UIDrawingContext& context, const RectF& clippedBounds, const RectF& bounds, Color color);
        };
    }

#endif