#include <Bibim/PCH.h>
#include <Bibim/SegmentShape2D.h>
#include <Bibim/Geom2D.h>
#include <Bibim/Math.h>
#include <Bibim/RaycastReport2D.h>

namespace Bibim
{
    SegmentShape2D::SegmentShape2D()
        : Shape2D(Shape2D::SegmentType),
          direction(Vector2::Zero),
          frontLength(0.0f),
          backLength(0.0f),
          startPoint(Vector2::Zero),
          endPoint(Vector2::Zero),
          rotatedDirection(Vector2::Zero),
          revision(0)
    {
    }

    SegmentShape2D::~SegmentShape2D()
    {
    }

    Vector2 SegmentShape2D::GetDirection() const
    {
        return direction;
    }

    void SegmentShape2D::SetDirection(Vector2 value)
    {
        if (value != Vector2::Zero)
            value.Normalize();

        if (GetDirection() != value)
        {
            direction = value;
            revision = 0;
        }
    }

    float SegmentShape2D::GetFrontLength() const
    {
        return frontLength;
    }

    void SegmentShape2D::SetFrontLength(float value)
    {
        value = Math::Max(value, 0.0f);

        if (GetFrontLength() != value)
        {
            frontLength = value;
            revision = 0;
        }
    }

    float SegmentShape2D::GetBackLength() const
    {
        return backLength;
    }

    void SegmentShape2D::SetBackLength(float value)
    {
        value = Math::Max(value, 0.0f);

        if (GetBackLength() != value)
        {
            backLength = value;
            revision = 0;
        }
    }

    Vector2 SegmentShape2D::GetStartPoint()
    {
        if (revision != GetSpatialRevision())
            UpdateParameters();

        return startPoint;
    }

    Vector2 SegmentShape2D::GetEndPoint()
    {
        if (revision != GetSpatialRevision())
            UpdateParameters();

        return endPoint;
    }

    float SegmentShape2D::GetLength() const
    {
        return GetFrontLength() + GetBackLength();
    }

    Vector2 SegmentShape2D::GetRotatedDirection()
    {
        if (revision != GetSpatialRevision())
            UpdateParameters();

        return rotatedDirection;
    }

    void SegmentShape2D::UpdateParameters()
    {
        revision = GetSpatialRevision();
        rotatedDirection = direction;
        rotatedDirection.Rotate(GetRotation());
        startPoint = GetPosition() + (rotatedDirection * GetBackLength()  * GetScale());
        endPoint   = GetPosition() + (rotatedDirection * GetFrontLength() * GetScale());
    }

    bool SegmentShape2D::Raycast(const Ray2D& ray, RaycastReport2D& outReport, IRaycastCallback2D* callback)
    {
        float distance = 0.0f;
        if (Geom2D::RaycastSegment(ray.Origin, ray.Direction, ray.Length, GetStartPoint(), GetEndPoint(), distance))
        {
            if (callback == nullptr || callback->OnHit(distance * distance))
            {
                const Vector2 rotatedDirection = GetRotatedDirection();
                outReport.ImpactShape = this;
                outReport.ImpactPoint = ray.Origin + (ray.Direction * distance);
                outReport.ImpactNormal = Vector2(rotatedDirection.Y, rotatedDirection.X);
                outReport.ImpactDistance = distance;
                if (outReport.ImpactNormal.Dot(rotatedDirection) > 0.0f)
                    outReport.ImpactNormal = -outReport.ImpactNormal;

                return true;
            }
        }

        return false;
    }

    void SegmentShape2D::AppendTo(std::list<Vector2>& vertices)
    {
        if (GetScale() > 0.0f && GetLength() > 0.0f)
        {
            vertices.push_back(GetStartPoint());
            vertices.push_back(GetEndPoint());
        }
    }
}