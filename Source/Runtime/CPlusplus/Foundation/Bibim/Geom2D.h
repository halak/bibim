#pragma once
#ifndef __BIBIM_GEOM2D_H__
#define __BIBIM_GEOM2D_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/Vector2.h>
#   include <vector>

    namespace Bibim
    {
        class Geom2D
        {
            BBThisIsStaticClass(Geom2D);
            public:
                // Point - AxisAlignedBox
                static float GetPointAxisAlignedBoxDistanceSquared(Vector2 p, Vector2 min, Vector2 max);

                // Point - Segment
                static inline bool IntersectPointSegment(Vector2 p, Vector2 a, Vector2 b);
                static float GetPointSegmentDistanceSquared(Vector2 p, Vector2 a, Vector2 b);

                // Point - Box
                static inline bool IntersectPointBox(Vector2 p, Vector2 origin, Vector2 axisX, Vector2 axisY, Vector2 extension);
                static inline Vector2 GetPointBoxClosestPoint(Vector2 p, Vector2 origin, Vector2 axisX, Vector2 axisY, Vector2 extension);

                // Point - Polygon
                static bool IntersectPointPolygon(Vector2 point, std::vector<Vector2> polygon);

                // Segment - Segment
                static inline bool IntersectSegmentSegment(Vector2 a, Vector2 b, Vector2 c, Vector2 d);
                static bool IntersectSegmentSegment(Vector2 a, Vector2 b, Vector2 c, Vector2 d, float& outResult);

                // Segment - AxisAlignedBox
                static bool IntersectSegmentAxisAlignedBox(Vector2 start, Vector2 end, Vector2 leftTop, Vector2 rightBottom);

                // AxisAlignedBox - AxisAlignedBox
                static inline bool IntersectAxisAlignedBoxAxisAlignedBox(Vector2 leftTop1, Vector2 rightBottom1, Vector2 leftTop2, Vector2 rightBottom2);

                // Box - Box
                static bool IntersectBoxBox(Vector2 center1, Vector2 orientation1, Vector2 extension1, Vector2 center2, Vector2 orientation2, Vector2 extension2);

                // Raycast
                static bool RaycastSegment(Vector2 origin, Vector2 direction, float length, Vector2 start, Vector2 end, float& outDistance);
                static bool RaycastSphere(Vector2 origin, Vector2 direction, Vector2 center, float radiusSquared, float& outDistance);
                static bool RaycastAxisAlignedBox(Vector2 origin, Vector2 direction, Vector2 leftTop, Vector2 rightBottom, float& outDistance, Vector2& outNormal);
                static bool RaycastBox(Vector2 origin, Vector2 direction, Vector2 center, Vector2 orientation, Vector2 extension, float& outDistance, Vector2& outNormal);
        };
    }

#   include <Bibim/Geom2D.inl>

#endif