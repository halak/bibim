#pragma once
#ifndef __BIBIM_UIRECT_H__
#define __BIBIM_UIRECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIVisual.h>
#   include <Bibim/Color.h>

    namespace Bibim
    {
        class UIRect : public UIVisual
        {
            BBComponentClass(UIRect, UIVisual, 'U', 'R', 'C', 'T');
            public:
                UIRect();
                virtual ~UIRect();

                inline Color GetFillColor() const;
                inline void SetFillColor(Color value);

                inline float GetFillColorR() const;
                inline float GetFillColorG() const;
                inline float GetFillColorB() const;
                inline void SetFillColorRGB(float r, float g, float b);

            protected:
                virtual void OnDraw(UIDrawingContext& context);

            private:
                Color fillColor;
        };
    }

#   include <Bibim/UIRect.inl>

#endif