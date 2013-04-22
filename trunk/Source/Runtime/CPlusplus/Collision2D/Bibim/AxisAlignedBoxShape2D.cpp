#include <Bibim/Config.h>
#include <Bibim/AxisAlignedBoxShape2D.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Geom2D.h>
#include <Bibim/Math.h>
#include <Bibim/RaycastReport2D.h>

namespace Bibim
{
    BBImplementsComponent(AxisAlignedBoxShape2D);

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

    void AxisAlignedBoxShape2D::SetMin(Vector2 value)
    {
        if (GetMin() != value)
        {
            min = value;
            revision = 0;
        }
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

    bool AxisAlignedBoxShape2D::Raycast(Vector2 origin, Vector2 direction, float length, RaycastReport2D& outReport, IRaycastCallback2D* callback)
    {
        float distance = 0.0f;
        Vector2 normal = Vector2::Zero;
        if (Geom2D::RaycastAxisAlignedBox(origin, direction, GetScaledMin(), GetScaledMax(), distance, normal) && distance <= length)
        {
            if (callback == nullptr || callback->OnHit(distance * distance))
            {
                outReport.ImpactShape = this;
                outReport.ImpactPoint = origin + (direction * distance);
                outReport.ImpactNormal = normal;
                outReport.ImpactDistance = distance;
                return true;
            }
        }

        return false;
    }

    void AxisAlignedBoxShape2D::Build(Vertices& vertices)
    {
        if (GetScale() > 0.0f)
        {
            const Vector2 scaledMin = GetScaledMin();
            const Vector2 scaledMax = GetScaledMax();
            vertices.Append(Vector2(scaledMin.X, scaledMin.Y),
                            Vector2(scaledMax.X, scaledMin.Y),
                            Vector2(scaledMax.X, scaledMax.Y),
                            Vector2(scaledMin.X, scaledMax.Y));
        }
    }

    void AxisAlignedBoxShape2D::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        min = reader.ReadVector2();
        max = reader.ReadVector2();
        revision = 0;
    }

    void AxisAlignedBoxShape2D::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        min = o->min;
        max = o->max;
        scaledMin = o->scaledMin;
        scaledMax = o->scaledMax;
        revision = o->revision;
    }

}