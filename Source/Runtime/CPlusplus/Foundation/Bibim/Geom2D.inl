#include <Bibim/Math.h>

namespace Bibim
{
    bool Geom2D::IntersectPointSegment(Vector2 p, Vector2 a, Vector2 b)
    {
        return GetPointSegmentDistanceSquared(p, a, b) < 0.01f; // 근사 값
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Geom2D::IntersectPointBox(Vector2 p, Vector2 origin, Vector2 axisX, Vector2 axisY, Vector2 extension)
    {
        return Math::Equals(p, GetPointBoxClosestPoint(p, origin, axisX, axisY, extension));
    }

    Vector2 Geom2D::GetPointBoxClosestPoint(Vector2 p, Vector2 origin, Vector2 axisX, Vector2 axisY, Vector2 extension)
    {
        const Vector2 d = p - origin;
        return origin + (axisX * Math::Clamp(d.Dot(axisX), -extension.X, +extension.X)) + (axisY * Math::Clamp(d.Dot(axisY), -extension.Y, +extension.Y));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Geom2D::IntersectSegmentSegment(Vector2 a, Vector2 b, Vector2 c, Vector2 d)
    {
        float t = 0.0f;
        return IntersectSegmentSegment(a, b, c, d, t);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Geom2D::IntersectAxisAlignedBoxAxisAlignedBox(Vector2 leftTop1, Vector2 rightBottom1, Vector2 leftTop2, Vector2 rightBottom2)
    {
        if (rightBottom1.X < leftTop2.X || leftTop1.X > rightBottom2.X)
            return false;
        if (rightBottom1.Y < leftTop2.Y || leftTop1.Y > rightBottom2.Y)
            return false;

        return true;
    }
}