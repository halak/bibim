#pragma once
#ifndef __BIBIM_UIELLIPSE_H__
#define __BIBIM_UIELLIPSE_H__

#include <Bibim/FWD.h>
#include <Bibim/UIShape.h>

namespace Bibim
{
    class UIEllipse : public UIShape
    {
        BBComponentClass(UIEllipse, UIShape, 'U', 'E', 'P', 'S');
        public:
            UIEllipse();
            virtual ~UIEllipse();

        protected:
            virtual void FillShape(UIDrawingContext& context, const RectF& clippedBounds, const RectF& bounds, Color color);
            virtual void DrawShape(UIDrawingContext& context, const RectF& clippedBounds, const RectF& bounds, Color color);
    };
}

#endif