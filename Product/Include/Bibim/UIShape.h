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

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Color UIShape::GetFillColor() const
        {
            return fillColor;
        }

        void UIShape::SetFillColor(Color value)
        {
            fillColor = value;
        }

        float UIShape::GetFillColorR() const
        {
            return fillColor.GetR();
        }

        float UIShape::GetFillColorG() const
        {
            return fillColor.GetG();
        }

        float UIShape::GetFillColorB() const
        {
            return fillColor.GetB();
        }

        void UIShape::SetFillColorRGB(float r, float g, float b)
        {
            SetFillColor(Color(Vector3(r, g, b)));
        }

        Color UIShape::GetLineColor() const
        {
            return lineColor;
        }

        void UIShape::SetLineColor(Color value)
        {
            lineColor = value;
        }

        float UIShape::GetLineColorR() const
        {
            return lineColor.GetR();
        }

        float UIShape::GetLineColorG() const
        {
            return lineColor.GetG();
        }

        float UIShape::GetLineColorB() const
        {
            return lineColor.GetB();
        }

        void UIShape::SetLineColorRGB(float r, float g, float b)
        {
            SetLineColor(Color(Vector3(r, g, b)));
        }
    }

#endif