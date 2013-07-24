#pragma once
#ifndef __BIBIM_UIROUNDEDRECT_H__
#define __BIBIM_UIROUNDEDRECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIShape.h>
#   include <Bibim/Math.h>

    namespace Bibim
    {
        class UIRoundedRect : public UIShape
        {
            BBComponentClass(UIRoundedRect, UIShape, 'U', 'R', 'R', 'T');
            public:
                UIRoundedRect();
                UIRoundedRect(float leftTop, float rightTop, float leftBottom, float rightBottom);
                virtual ~UIRoundedRect();

                inline float GetLeftTopRadius() const;
                inline void  SetLeftTopRadius(float value);
                inline float GetRightTopRadius() const;
                inline void  SetRightTopRadius(float value);
                inline float GetLeftBottomRadius() const;
                inline void  SetLeftBottomRadius(float value);
                inline float GetRightBottomRadius() const;
                inline void  SetRightBottomRadius(float value);

                inline void Setup(float leftTop, float rightTop, float leftBottom, float rightBottom);
                inline void SetAllRadii(float value);
                inline void SetLeftRadii(float value);
                inline void SetTopRadii(float value);
                inline void SetRightRadii(float value);
                inline void SetBottomRadii(float value);

            protected:
                virtual void FillShape(UIDrawingContext& context, const RectF& clippedBounds, const RectF& bounds, Color color);
                virtual void DrawShape(UIDrawingContext& context, const RectF& clippedBounds, const RectF& bounds, Color color);

            private:
                float leftTop;
                float rightTop;
                float leftBottom;
                float rightBottom;
        };
    }

#endif