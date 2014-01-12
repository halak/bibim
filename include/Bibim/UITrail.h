#pragma once
#ifndef __BIBIM_UITRAIL_H__
#define __BIBIM_UITRAIL_H__

#include <Bibim/FWD.h>
#include <Bibim/UIVisual.h>
#include <deque>
#include <vector>

namespace Bibim
{
    class UITrail : public UIVisual
    {
        BBComponentClass(UITrail, UIVisual, 'U', 'T', 'R', 'L');
        public:
            UITrail();
            virtual ~UITrail();

            void Clear();

            inline float GetThickness() const;
            void SetThickness(float value);

            inline int GetTrails() const;
            void SetTrails(int value);

            inline Texture2D* GetSource() const;
            void SetSource(Texture2D* value);

            virtual Vector2 GetContentSize();

        protected:
            virtual void OnDraw(UIDrawingContext& context);

        private:
            float thickness;
            int numberOfTrails;
            Texture2DPtr source;
            std::deque<Vector2> trails;
            std::deque<Vector2> lines1;
            std::deque<Vector2> lines2;
            std::vector<Vector2> triangles;
            std::vector<Vector2> triangleUVs;
            std::vector<Color> triangleColors;
            std::vector<Color> triangleColorsTemporary;
            Vector2 lastDirection;
            float trailLength;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    float UITrail::GetThickness() const
    {
        return thickness;
    }

    int UITrail::GetTrails() const
    {
        return numberOfTrails;
    }

    Texture2D* UITrail::GetSource() const
    {
        return source;
    }

}

#endif