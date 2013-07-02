#pragma once
#ifndef __BIBIM_GEOM2D_H__
#define __BIBIM_GEOM2D_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/Math.h>
#   include <Bibim/Point2.h>
#   include <Bibim/Vector2.h>
#   include <vector>

    namespace Bibim
    {
        /// @brief 2차원 기하 수학 함수들이 주로 정의되어 있는 static class.
        /// AABB (Axis-aligned box) <br />
        /// OBB (Oriented box) <br />
        class Geom2D
        {
            BBThisIsStaticClass(Geom2D);
            public:
                ///@name Point - AxisAlignedBox
                ///@{
                    /// @brief 입력한 점과 사각형(AABB) 사이의 최단 거리의 제곱을 반환합니다.
                    /// @param[in] p   점 위치
                    /// @param[in] min 사각형의 좌측상단 점 위치
                    /// @param[in] max 사각형의 우측하단 점 위치
                    /// @pre
                    /// min.X < max.X <i>AND</i> <br />
                    /// min.Y < max.Y
                    static int   GetPointAxisAlignedBoxDistanceSquared(Point2  p, Point2  min, Point2 max);
                    static float GetPointAxisAlignedBoxDistanceSquared(Vector2 p, Vector2 min, Vector2 max);
                ///@}

                ///@name Point - Segment
                ///@{
                    /// @brief 입력한 점이 선분 위에 존재하는지 확인합니다.
                    /// @param[in] p 점 위치
                    /// @param[in] a 선분의 시작점 위치
                    /// @param[in] b 선분의 끝점 위치
                    static inline bool IntersectPointSegment(Vector2 p, Vector2 a, Vector2 b);

                    /// @brief 입력한 점과 선 사이의 최단 거리의 제곱을 반환합니다.
                    /// @param[in] p 점 위치
                    /// @param[in] a 선분의 시작점 위치
                    /// @param[in] b 선분의 끝점 위치
                    static int   GetPointSegmentDistanceSquared(Point2  p, Point2  a, Point2  b);
                    static float GetPointSegmentDistanceSquared(Vector2 p, Vector2 a, Vector2 b);
                ///@}

                ///@name Point - Box
                ///@{
                    /// @brief 입력한 점이 사각형(OBB) 안에 존재하는지 확인합니다.
                    /// @param[in] p 점 위치
                    /// @param[in] origin 사각형의 원점
                    /// @param[in] axisX 사각형의 가로축 방향
                    /// @param[in] axisY 사각형의 세로축 방향
                    /// @param[in] extension 사각형의 가로/세로 크기
                    /// @pre
                    /// axisX, axisY는 단위 Vector <i>AND</i> <br />
                    /// axisX, axisY는 서로 직각 <i>AND</i> <br />
                    /// extension.X > 0 <i>AND</i> <br />
                    /// extension.Y > 0
                    static inline bool IntersectPointBox(Vector2 p, Vector2 origin, Vector2 axisX, Vector2 axisY, Vector2 extension);

                    /// @brief 입력한 점과 사각형(OBB) 사이의 가장 가까운 점의 위치를 반환합니다.
                    /// @param[in] p 점 위치
                    /// @param[in] origin 사각형의 원점
                    /// @param[in] axisX 사각형의 가로축 방향
                    /// @param[in] axisY 사각형의 세로축 방향
                    /// @param[in] extension 사각형의 가로/세로 크기
                    /// @pre
                    /// axisX, axisY는 단위 Vector <i>AND</i> <br />
                    /// axisX, axisY는 서로 직각 <i>AND</i> <br />
                    /// extension.X > 0 <i>AND</i> <br />
                    /// extension.Y > 0
                    static inline Vector2 GetPointBoxClosestPoint(Vector2 p, Vector2 origin, Vector2 axisX, Vector2 axisY, Vector2 extension);
                ///@}

                ///@name Point - Polygon
                ///@{
                    /// @brief 입력한 점이 다각형 안에 존재하는지 확인합니다.
                    /// @param[in] p 점 위치
                    /// @param[in] polygon 다각형의 꼭지점
                    static bool IntersectPointPolygon(Vector2 point, std::vector<Vector2> polygon);
                ///@}

                ///@name Segment - Segment
                ///@{
                    /// @brief 입력한 두 선분이 서로 교차하는지 확인합니다.
                    /// @param[in] a 첫번째 선분의 시작점 위치
                    /// @param[in] b 첫번째 선분의 끝점 위치
                    /// @param[in] c 두번째 선분의 시작점 위치
                    /// @param[in] d 두번째 선분의 끝점 위치
                    static inline bool IntersectSegmentSegment(Vector2 a, Vector2 b, Vector2 c, Vector2 d);

                    /// @brief 입력한 두 선분이 서로 교차하는지 확인하고 교차하는 점의 위치도 반환합니다.
                    /// @param[in] a 첫번째 선분의 시작점 위치
                    /// @param[in] b 첫번째 선분의 끝점 위치
                    /// @param[in] c 두번째 선분의 시작점 위치
                    /// @param[in] d 두번째 선분의 끝점 위치
                    /// @param[out] outResult 두 선분이 교차하는 점의 첫번째 선분을 기저로 한 위치 (교차점 = (a + (b - a) * outResult))
                    static bool IntersectSegmentSegment(Vector2 a, Vector2 b, Vector2 c, Vector2 d, float& outResult);
                ///@}

                ///@name Segment - AxisAlignedBox
                ///@{
                    /// @brief 입력한 선분과 사각형(AABB)가 교차하는지 확인합니다.
                    /// @param[in] start 선분의 시작점 위치
                    /// @param[in] end   선분의 끝점 위치
                    /// @param[in] leftTop     사각형의 좌측상단 점 위치
                    /// @param[in] rightBottom 사각형의 우측하단 점 위치
                    static bool IntersectSegmentAxisAlignedBox(Vector2 start, Vector2 end, Vector2 leftTop, Vector2 rightBottom);
                ///@}

                ///@name AxisAlignedBox - AxisAlignedBox
                ///@{
                    /// @brief 입력한 두 사각형(AABB)가 서로 교차하는지 확인합니다.
                    /// @param[in] leftTop1     첫번째 사각형의 좌측상단 점 위치
                    /// @param[in] rightBottom1 첫번째 사각형의 우측하단 점 위치
                    /// @param[in] leftTop2     두번째 사각형의 좌측상단 점 위치
                    /// @param[in] rightBottom2 두번째 사각형의 우측하단 점 위치
                    static inline bool IntersectAxisAlignedBoxAxisAlignedBox(Vector2 leftTop1, Vector2 rightBottom1, Vector2 leftTop2, Vector2 rightBottom2);
                ///@}

                ///@name Box - Box
                ///@{
                    /// @brief 입력한 두 사각형(OBB)가 서로 교차하는지 확인합니다.
                    /// @param[in] center1      첫번째 사각형의 원점
                    /// @param[in] orientation1 첫번째 사각형의 방향
                    /// @param[in] extension1   첫번째 사각형의 가로/세로 크기
                    /// @param[in] center2      두번째 사각형의 원점
                    /// @param[in] orientation2 두번째 사각형의 방향
                    /// @param[in] extension2   두번째 사각형의 가로/세로 크기
                    /// @pre
                    /// orientation1, orientation2는 단위 Vector
                    static bool IntersectBoxBox(Vector2 center1, Vector2 orientation1, Vector2 extension1, Vector2 center2, Vector2 orientation2, Vector2 extension2);
                ///@}

                ///@name Raycast
                ///@{
                    /// @brief Ray가 선분에 도달하는지 확인합니다.
                    /// @param[in]  origin    Ray의 원점
                    /// @param[in]  direction Ray의 방향
                    /// @param[in]  length    Ray의 길이
                    /// @param[in]  start     선분의 시작점 위치
                    /// @param[in]  end       선분의 끝점 위치
                    /// @param[out] outDistance 도달하는 점의 Ray로부터의 거리
                    /// @pre
                    /// direction은 단위 Vector <i>AND</i><br />
                    /// length > 0
                    static bool RaycastSegment(Vector2 origin, Vector2 direction, float length, Vector2 start, Vector2 end, float& outDistance);

                    /// @brief Ray가 원에 도달하는지 확인합니다.
                    /// @param[in]  origin    Ray의 원점
                    /// @param[in]  direction Ray의 방향
                    /// @param[in]  center        원의 중점
                    /// @param[in]  radiusSquared 원의 반지름의 제곱
                    /// @param[out] outDistance   도달하는 점의 Ray로부터의 거리
                    /// @pre
                    /// direction은 단위 Vector <i>AND</i><br />
                    /// radiusSquared > 0
                    static bool RaycastSphere(Vector2 origin, Vector2 direction, Vector2 center, float radiusSquared, float& outDistance);

                    /// @brief Ray가 사각형(AABB)에 도달하는지 확인합니다.
                    /// @param[in]  origin    Ray의 원점
                    /// @param[in]  direction Ray의 방향
                    /// @param[in]  leftTop     선분의 시작점 위치
                    /// @param[in]  rightBottom 선분의 끝점 위치
                    /// @param[out] outDistance 도달하는 점의 Ray로부터의 거리
                    /// @param[out] outNormal   도달하는 점의 법선 Vector
                    /// @pre
                    /// direction은 단위 Vector <i>AND</i><br />
                    /// leftTop.X < rightBottom.X <i>AND</i><br />
                    /// leftTop.Y < rightBottom.Y
                    static bool RaycastAxisAlignedBox(Vector2 origin, Vector2 direction, Vector2 leftTop, Vector2 rightBottom, float& outDistance, Vector2& outNormal);

                    /// @brief Ray가 사각형(OBB)에 도달하는지 확인합니다.
                    /// @param[in]  origin    Ray의 원점
                    /// @param[in]  direction Ray의 방향
                    /// @param[in]  center      사각형의 원점
                    /// @param[in]  orientation 사각형의 방향
                    /// @param[in]  extension   사각형의 가로/세로 크기
                    /// @param[out] outDistance 도달하는 점의 Ray로부터의 거리
                    /// @param[out] outNormal   도달하는 점의 법선 Vector
                    /// @pre
                    /// direction, orientation은 단위 Vector <i>AND</i><br />
                    static bool RaycastBox(Vector2 origin, Vector2 direction, Vector2 center, Vector2 orientation, Vector2 extension, float& outDistance, Vector2& outNormal);
                ///@}

                ///@name Misc
                ///@{
                    /// @brief 입력한 선분을 이루는 점 중 입력한 점과 가장 가까운 점의 위치를 반환합니다.
                    /// @param[in] origin 선분의 원점
                    /// @param[in] direction 선분의 방향
                    /// @param[in] length 선분의 길이
                    /// @param[in] point 점의 위치
                    /// @pre
                    /// direction은 단위 Vector <i>AND</i> <br />
                    /// length > 0
                    static Vector2 GetClosestPoint(Vector2 origin, Vector2 direction, float length, Vector2 point);

                    /// 입력한 점들이 시계방향으로 감기는지 확인합니다.
                    static bool IsClockwise(Vector2 a, Vector2 b, Vector2 c);
                    /// 입력한 점들이 시계방향으로 감기는지 확인합니다.
                    static bool IsClockwise(const Vector2* points, int numberOfPoints);
                ///@}
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

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

#endif