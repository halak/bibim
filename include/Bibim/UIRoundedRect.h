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

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        float UIRoundedRect::GetLeftTopRadius() const
        {
            return leftTop;
        }

        void UIRoundedRect::SetLeftTopRadius(float value)
        {
            leftTop = Math::Max(value, 0.0f);
        }

        float UIRoundedRect::GetRightTopRadius() const
        {
            return rightTop;
        }

        void UIRoundedRect::SetRightTopRadius(float value)
        {
            rightTop = Math::Max(value, 0.0f);
        }

        float UIRoundedRect::GetLeftBottomRadius() const
        {
            return leftBottom;
        }

        void UIRoundedRect::SetLeftBottomRadius(float value)
        {
            leftBottom = Math::Max(value, 0.0f);
        }

        float UIRoundedRect::GetRightBottomRadius() const
        {
            return rightBottom;
        }

        void UIRoundedRect::SetRightBottomRadius(float value)
        {
            rightBottom = Math::Max(value, 0.0f);
        }
        
        void UIRoundedRect::Setup(float leftTop, float rightTop, float leftBottom, float rightBottom)
        {
            SetLeftTopRadius(leftTop);
            SetRightTopRadius(rightTop);
            SetLeftBottomRadius(leftBottom);
            SetRightBottomRadius(rightBottom);
        }

        void UIRoundedRect::SetAllRadii(float value)
        {
            Setup(value, value, value, value);
        }

        void UIRoundedRect::SetLeftRadii(float value)
        {
            SetLeftTopRadius(value);
            SetLeftBottomRadius(value);
        }

        void UIRoundedRect::SetTopRadii(float value)
        {
            SetLeftTopRadius(value);
            SetRightTopRadius(value);
        }

        void UIRoundedRect::SetRightRadii(float value)
        {
            SetRightTopRadius(value);
            SetRightBottomRadius(value);
        }

        void UIRoundedRect::SetBottomRadii(float value)
        {
            SetLeftBottomRadius(value);
            SetRightBottomRadius(value);
        }
    }

#endif