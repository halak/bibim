#pragma once
#ifndef __BIBIM_UIDEBUGDRAWMIXIN_H__
#define __BIBIM_UIDEBUGDRAWMIXIN_H__

#include <Bibim/FWD.h>
#include <Bibim/Color.h>
#include <Bibim/RectF.h>
#include <Bibim/Vector2.h>
#include <vector>

namespace Bibim
{
    class UIDebugDrawMixin
    {
        public:
            UIDebugDrawMixin();
            ~UIDebugDrawMixin();

            inline void DrawDebugLine(Vector2 start, Vector2 end, Color color, float time = 0.0f);
            void DrawDebugLine(Vector2 start, Vector2 end, float thickness, Color color, float time = 0.0f);
            void DrawDebugRay(Vector2 origin, Vector2 direction, float length, Color color, float time = 0.0f);
            void DrawDebugRect(RectF bounds, Color color, float time = 0.0f);

        protected:
            void Flush(UIDrawingContext& context, float dt = 0.0f);

        private:
            struct DebugLine
            {
                Vector2 start;
                Vector2 end;
                Color color;
                float thickness;
                float time;
            };

            struct DebugRect
            {
                RectF bounds;
                Color color;
                float time;
            };

            template <typename T> void Flush(UIDrawingContext& context, float dt, std::vector<T>& geometries);
            void Flush(UIDrawingContext& context, const DebugLine& geom);
            void Flush(UIDrawingContext& context, const DebugRect& geom);

        private:
            std::vector<DebugLine> lines;
            std::vector<DebugRect> rects;

    };

    void UIDebugDrawMixin::DrawDebugLine(Vector2 start, Vector2 end, Color color, float time)
    {
        DrawDebugLine(start, end, 1.0f, color, time);
    }
}

#endif