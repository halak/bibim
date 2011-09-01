#include <Bibim/PCH.h>
#include <Bibim/AxisAlignedBoxShape2D.h>
#include <Bibim/Geom2D.h>
#include <Bibim/Math.h>
#include <Bibim/RaycastReport2D.h>

namespace Bibim
{
    AxisAlignedBoxShape2D::AxisAlignedBoxShape2D()
        : Shape2D(Shape2D::AxisAlignedBoxType),
          min(Vector2::Zero),
          max(Vector2::Zero),
          scaledMin(Vector2::Zero),
          scaledMax(Vector2::Zero),
          revision(0)
    {
    }

    AxisAlignedBoxShape2D::~AxisAlignedBoxShape2D()
    {
    }

    Vector2 AxisAlignedBoxShape2D::GetMin() const
    {
        return min;
    }

    void AxisAlignedBoxShape2D::SetMin(Vector2 value)
    {
        if (GetMin() != value)
        {
            min = value;
            revision = 0;
        }
    }

    Vector2 AxisAlignedBoxShape2D::GetMax() const
    {
        return max;
    }

    void AxisAlignedBoxShape2D::SetMax(Vector2 value)
    {
        if (GetMax() != value)
        {
            max = value;
            revision = 0;
        }
    }

    Vector2 AxisAlignedBoxShape2D::GetScaledMin()
    {
        if (revision != GetSpatialRevision())
            UpdateParameters();

        return scaledMin;
    }

    Vector2 AxisAlignedBoxShape2D::GetScaledMax()
    {
        if (revision != GetSpatialRevision())
            UpdateParameters();

        return scaledMax;
    }

    void AxisAlignedBoxShape2D::UpdateParameters()
    {
        revision  = GetSpatialRevision();
        scaledMin = GetMin() * GetScale();
        scaledMax = GetMax() * GetScale();
    }

    bool AxisAlignedBoxShape2D::Raycast(const Ray2D& ray, RaycastReport2D& outReport, IRaycastCallback2D* callback)
    {
        float distance = 0.0f;
        Vector2 normal = Vector2::Zero;
        if (Geom2D::RaycastAxisAlignedBox(ray.Origin, ray.Direction, GetScaledMin(), GetScaledMax(), distance, normal) && distance <= ray.Length)
        {
            if (callback == nullptr || callback->OnHit(distance * distance))
            {
                outReport.ImpactShape = this;
                outReport.ImpactPoint = ray.Origin + (ray.Direction * distance);
                outReport.ImpactNormal = normal;
                outReport.ImpactDistance = distance;
                return true;
            }
        }

        return false;
    }

    void AxisAlignedBoxShape2D::AppendTo(std::list<Vector2>& vertices)
    {
        if (GetScale() > 0.0f)
        {
            const Vector2 scaledMin = GetScaledMin();
            const Vector2 scaledMax = GetScaledMax();
            vertices.push_back(Vector2(scaledMin.X, scaledMin.Y));
            vertices.push_back(Vector2(scaledMax.X, scaledMin.Y));
            vertices.push_back(Vector2(scaledMax.X, scaledMax.Y));
            vertices.push_back(Vector2(scaledMin.X, scaledMax.Y));
        }
    }
}