#include <Bibim/Config.h>
#include <Bibim/UIDebugDrawMixin.h>
#include <Bibim/UIDrawingContext.h>

namespace Bibim
{
    UIDebugDrawMixin::UIDebugDrawMixin()
    {
    }

    UIDebugDrawMixin::~UIDebugDrawMixin()
    {
    }

    void UIDebugDrawMixin::DrawDebugLine(Vector2 start, Vector2 end, float thickness, Color color, float time)
    {
        DebugLine o;
        o.start = start;
        o.end = end;
        o.color = color;
        o.thickness = thickness;
        o.time = time;
        lines.push_back(o);
    }

    void UIDebugDrawMixin::DrawDebugRay(Vector2 origin, Vector2 direction, float length, Color color, float time)
    {
        DebugLine o;
        o.start = origin;
        o.end = origin + direction * length;
        o.color = color;
        o.thickness = 1.0f;
        o.time = time;
        lines.push_back(o);

        const Vector2 end = origin + direction * length;
        const Vector2 normal = Vector2(-direction.Y, direction.X);
        DrawDebugLine(origin, end, color, time);
        DrawDebugLine(end, end + (normal - direction) * 5.0f, color, time);
        DrawDebugLine(end, end - (normal + direction) * 5.0f, color, time);
    }

    void UIDebugDrawMixin::DrawDebugRect(RectF bounds, Color color, float time)
    {
        DebugRect o;
        o.bounds = bounds;
        o.color = color;
        o.time = time;
        rects.push_back(o);
    }

    template <typename T> void UIDebugDrawMixin::Flush(UIDrawingContext& context, float dt, std::vector<T>& geometries)
    {
        for (typename std::vector<T>::iterator it = geometries.begin(); it != geometries.end();)
        {
            T& o = (*it);

            Flush(context, o);

            o.time -= dt;

            if (o.time > 0.0f)
                it++;
            else
                it = geometries.erase(it);
        }
    }

    void UIDebugDrawMixin::Flush(UIDrawingContext& context, const DebugLine& geom)
    {
        context.DrawDebugLine(geom.start, geom.end, geom.color);
    }

    void UIDebugDrawMixin::Flush(UIDrawingContext& context, const DebugRect& geom)
    {
        context.DrawDebugRect(geom.bounds, geom.color);
    }

    void UIDebugDrawMixin::Flush(UIDrawingContext& context, float dt)
    {
        Flush(context, dt, lines);
        Flush(context, dt, rects);
    }
}