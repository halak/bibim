#pragma once
#ifndef __BIBIM_UISHAPE_H__
#define __BIBIM_UISHAPE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIVisual.h>
#   include <Bibim/Color.h>

    namespace Bibim
    {
        class UIShape : public UIVisual
        {
            BBAbstractComponentClass(UIShape, UIVisual);
            public:
                UIShape();
                virtual ~UIShape();

                inline Color GetFillColor() const;
                inline void SetFillColor(Color value);

                inline Color GetLineColor() const;
                inline void SetLineColor(Color value);

                inline float GetFillColorR() const;
                inline float GetFillColorG() const;
                inline float GetFillColorB() const;
                inline void SetFillColorRGB(float r, float g, float b);

                inline float GetLineColorR() const;
                inline float GetLineColorG() const;
                inline float GetLineColorB() const;
                inline void SetLineColorRGB(float r, float g, float b);

            protected:
                virtual void OnDraw(UIDrawingContext& context);

                virtual void FillShape(UIDrawingContext& context, const RectF& clippedBounds, const RectF& bounds, Color color) = 0;
                virtual void DrawShape(UIDrawingContext& context, const RectF& clippedBounds, const RectF& bounds, Color color) = 0;

            private:
                Color fillColor;
                Color lineColor;
        };
    }

#   include <Bibim/UIShape.inl>

#endif