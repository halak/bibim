#include <Bibim/Config.h>
#include <Bibim/Geom2D.h>
#include <Bibim/Assert.h>
#include <Bibim/Math.h>
#include <Bibim/Numerics.h>

namespace Bibim
{
    float Geom2D::GetPointAxisAlignedBoxDistanceSquared(Vector2 p, Vector2 min, Vector2 max)
    {
        float result = 0.0f;

        BBAssert(!((p.X < min.X && p.X > max.X) || (p.Y < min.Y && p.Y > max.Y)));

        if (p.X < min.X)
            result += (min.X - p.X) * (min.X - p.X);
        else if (p.X > max.X)
            result += (p.X - max.X) * (p.X - max.X);
        if (p.Y < min.Y)
            result += (min.Y - p.Y) * (min.Y - p.Y);
        else if (p.Y > max.Y)
            result += (p.Y - max.Y) * (p.Y - max.Y);

        return result;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    float Geom2D::GetPointSegmentDistanceSquared(Vector2 p, Vector2 a, Vector2 b)
    {
        const Vector2 ab = b - a;
        const Vector2 ap = p - a;
        const Vector2 bp = p - b;
        const float e = ab.Dot(ap);

        if (e > 0.0f)
        {
            const float f = ab.Dot(ab);
            if (e >= f)
                return bp.Dot(bp);
            else
                return ap.Dot(ap) - e * e / f;
        }
        else
            return ap.Dot(ap);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Geom2D::IntersectPointPolygon(Vector2 point, std::vector<Vector2> polygon)
    {
        bool result = false;

        for (std::vector<Vector2>::size_type i = 0, k = polygon.size() - 1; i < polygon.size(); k = i++)
        {
            if (((polygon[i].Y > point.Y) != (polygon[k].Y > point.Y)) &&
                (point.X < (polygon[k].X - polygon[i].X) * (point.Y - polygon[i].Y) / (polygon[k].Y - polygon[i].Y) + polygon[i].X))
            {
                result = !result;
            }
        }

        return result;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    static inline float Signed2DTriArea(Vector2 a, Vector2 b, Vector2 c)
    {
        return (a.X - c.X) * (b.Y - c.Y) - (a.Y - c.Y) * (b.X - c.X);
    }

    bool Geom2D::IntersectSegmentSegment(Vector2 a, Vector2 b, Vector2 c, Vector2 d, float& outResult)
    {
        float a1 = Signed2DTriArea(a, b, d);
        float a2 = Signed2DTriArea(a, b, c);
        if (a1 * a2 < 0.0f)
        {
            float a3 = Signed2DTriArea(c, d, a);
            float a4 = a3 + a2 - a1;
            if (a3 * a4 < 0.0f)
            {
                outResult = a3 / (a3 - a4);
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Geom2D::IntersectSegmentAxisAlignedBox(Vector2 start, Vector2 end, Vector2 leftTop, Vector2 rightBottom)
    {
        const Vector2 c = (leftTop + rightBottom) * 0.5f;
        const Vector2 e = rightBottom - c;
        Vector2 m = (start + end) * 0.5f;
        const Vector2 d = end - m;

        m.X -= c.X;
        m.Y -= c.Y;

        float adx = Math::Abs(d.X);
        if (Math::Abs(m.X) > e.X + adx)
            return false;

        float ady = Math::Abs(d.Y);
        if (Math::Abs(m.Y) > e.Y + ady)
            return false;

        adx += 0.0001f;
        ady += 0.0001f;

        return Math::Abs(m.X * d.Y - m.Y * d.X) <= e.X * ady + e.Y * adx;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Geom2D::IntersectBoxBox(Vector2 center1, Vector2 orientation1, Vector2 extension1, Vector2 center2, Vector2 orientation2, Vector2 extension2)
    {
        const Vector2 up1 = Vector2(+orientation1.Y, -orientation1.X);
        const Vector2 up2 = Vector2(+orientation2.Y, -orientation2.X);

        const float R11 = orientation1.Dot(orientation2);
        const float R12 = orientation1.Dot(up2);
        const float R21 = up1.Dot(orientation2);
        const float R22 = up1.Dot(up2);

        const Vector2 center1ToCenter2 = center2 - center1;
        const Vector2 t = Vector2(center1ToCenter2.Dot(orientation1), center1ToCenter2.Dot(up1));

        const float A11 = Math::Abs(R11) + 0.0001f;
        const float A12 = Math::Abs(R12) + 0.0001f;
        const float A21 = Math::Abs(R21) + 0.0001f;
        const float A22 = Math::Abs(R22) + 0.0001f;

        float r1 = 0.0f;
        float r2 = 0.0f;

        r1 = extension1.X;
        r2 = extension2.X * A11 + extension2.Y * A12;
        if (Math::Abs(t.X) > r1 + r2)
            return false;
        r1 = extension1.Y;
        r2 = extension2.X * A21 + extension2.Y * A22;
        if (Math::Abs(t.Y) > r1 + r2)
            return false;

        r1 = extension1.X * A11 + extension1.Y * A21;
        r2 = extension2.X;
        if (Math::Abs(t.X * R11 + t.Y * R21) > r1 + r2)
            return false;
        r1 = extension1.X * A12 + extension1.Y * A22;
        r2 = extension2.Y;
        if (Math::Abs(t.X * R12 + t.Y * R22) > r1 + r2)
            return false;

        return true;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Geom2D::RaycastSegment(Vector2 origin, Vector2 direction, float length, Vector2 start, Vector2 end, float& outDistance)
    {
        float t = 0.0f;
        if (IntersectSegmentSegment(origin, origin + direction * length, start, end, t))
        {
            outDistance = t * length;
            return true;
        }
        else
            return false;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Geom2D::RaycastSphere(Vector2 origin, Vector2 direction, Vector2 center, float radiusSquared, float& outDistance)
    {
        const Vector2 m = origin - center;
        const float b = m.Dot(direction);
        const float c = m.Dot(m) - radiusSquared;

        if (c > 0.0f && b > 0.0f)
            return false;

        const float discriminant = (b * b) - c;
        if (discriminant >= 0.0f)
        {
            outDistance = Math::Max((-b) - static_cast<float>(Math::Sqrt(discriminant)), 0.0f);
            return true;
        }
        else
            return false;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Geom2D::RaycastAxisAlignedBox(Vector2 origin, Vector2 direction, Vector2 leftTop, Vector2 rightBottom, float& outDistance, Vector2& outNormal)
    {
        float tMin = 0.0f;
        float tMax = Float::Max;

        if (Math::Abs(direction.X) < 0.00001f)
        {
            if (origin.X < leftTop.X || rightBottom.X < origin.X)
                return false;
        }
        else
        {
            float ood = 1.0f / direction.X;
            float t1 = (leftTop.X - origin.X) * ood;
            float t2 = (rightBottom.X - origin.X) * ood;

            if (t1 <= t2)
            {
                if (tMin < t1)
                {
                    tMin = t1;
                    outNormal.X = -1.0f;
                    outNormal.Y = +0.0f;
                }
                tMax = Math::Min(tMax, t2);
            }
            else
            {
                if (tMin < t2)
                {
                    tMin = t2;
                    outNormal.X = +1.0f;
                    outNormal.Y = +0.0f;
                }
                tMax = Math::Min(tMax, t1);
            }

            if (tMin > tMax)
                return false;
        }

        if (Math::Abs(direction.Y) < 0.00001f)
        {
            if (origin.Y < leftTop.Y || rightBottom.Y < origin.Y)
                return false;
        }
        else
        {
            float ood = 1.0f / direction.Y;
            float t1 = (leftTop.Y - origin.Y) * ood;
            float t2 = (rightBottom.Y - origin.Y) * ood;

            if (t1 <= t2)
            {
                if (tMin < t1)
                {
                    tMin = t1;
                    outNormal.X = +0.0f;
                    outNormal.Y = -1.0f;
                }
                tMax = Math::Min(tMax, t2);
            }
            else
            {
                if (tMin < t2)
                {
                    tMin = t2;
                    outNormal.X = +0.0f;
                    outNormal.Y = +1.0f;
                }
                tMax = Math::Min(tMax, t1);
            }

            if (tMin > tMax)
                return false;
        }

        outDistance = tMin;
        return true;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Geom2D::RaycastBox(Vector2 origin, Vector2 direction, Vector2 center, Vector2 orientation, Vector2 extension, float& outDistance, Vector2& outNormal)
    {
        const float dot = orientation.Dot(Vector2::UnitX);
        float rotation = (float)Math::Acos(dot);
        if (orientation.Y > 0.0f)
            rotation = -rotation;

        const float sin = (float)Math::Sin(rotation);
        const float cos = (float)dot; // == Math.Cos(rotation)

        origin -= center;
        origin.Rotate(sin, cos);
        origin += center;
        direction.Rotate(sin, cos);

        const Vector2 leftTop = center - extension;
        const Vector2 rightBottom = center + extension;

        if (RaycastAxisAlignedBox(origin, direction, leftTop, rightBottom, outDistance, outNormal))
        {
            outNormal.Rotate(-sin, cos); // == normal.Rotate(-rotation)
            return true;
        }
        else
            return false;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2 Geom2D::GetClosestPoint(Vector2 origin, Vector2 direction, float length, Vector2 point)
    {
        return origin + (direction * Math::Clamp(direction.Dot(point - origin), 0.0f, length));
    }

    bool Geom2D::IsClockwise(Vector2 a, Vector2 b, Vector2 c)
    {
        // Right-handed
        // http://www.dsource.org/projects/blaze/changeset/63
        return ((b.X - a.X) * (c.Y - a.Y) - (c.X - a.X) * (b.Y - a.Y)) > 0.0f;
    }

    bool Geom2D::IsClockwise(const Vector2* points, int numberOfPoints)
    {
        const int last = numberOfPoints - 1;
        float crossProductSum = (points[last].X * points[0].Y) - (points[0].X * points[last].Y);
        for (int i = 0; i < last; i++)
        {
            crossProductSum += (points[i].X * points[i + 1].Y) - (points[i + 1].X * points[i].Y);
        }

        return crossProductSum > 0.0f;
    }

}