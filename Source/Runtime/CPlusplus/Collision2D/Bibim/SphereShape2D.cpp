#include <Bibim/PCH.h>
#include <Bibim/SphereShape2D.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Geom2D.h>
#include <Bibim/Math.h>
#include <Bibim/RaycastReport2D.h>

namespace Bibim
{
    BBImplementsComponent(SphereShape2D);

    SphereShape2D::SphereShape2D()
        : Shape2D(Shape2D::SphereType),
          radius(0.0f),
          radiusSquared(0.0f),
          scaledRadius(0.0f),
          scaledRadiusSquared(0.0f),
          revision(0)
    {
    }

    SphereShape2D::~SphereShape2D()
    {
    }

    float SphereShape2D::GetRadius() const
    {
        return radius;
    }
    
    void SphereShape2D::SetRadius(float value)
    {
        if (GetRadius() != value)
        {
            radius = value;
            radiusSquared = radius * radius;
            revision = 0;
        }
    }

    float SphereShape2D::GetScaledRadius()
    {
        if (revision != GetSpatialRevision())
            UpdateParameters();

        return scaledRadius;
    }

    float SphereShape2D::GetScaledRadiusSquared()
    {
        if (revision != GetSpatialRevision())              
            UpdateParameters();

        return scaledRadiusSquared;
    }

    void SphereShape2D::UpdateParameters()
    {
        revision = GetSpatialRevision();
        scaledRadius = GetRadius() * GetScale();
        scaledRadiusSquared = scaledRadius * scaledRadius;
    }

    bool SphereShape2D::Raycast(Vector2 origin, Vector2 direction, float length, RaycastReport2D& outReport, IRaycastCallback2D* callback)
    {
        float distance = 0.0f;
        if (Geom2D::RaycastSphere(origin, direction, GetPosition(), GetScaledRadiusSquared(), distance) && distance <= length)
        {
            if (callback == nullptr || callback->OnHit(distance * distance))
            {
                outReport.ImpactShape = this;
                outReport.ImpactPoint = origin + (direction * distance);
                outReport.ImpactNormal = outReport.ImpactPoint - GetPosition();
                outReport.ImpactNormal.Normalize();
                outReport.ImpactDistance = distance;
                return true;
            }
        }

        return false;
    }

    void SphereShape2D::AppendTo(std::list<Vector2>& vertices)
    {
        const float scaledRadius = GetScaledRadius();
        if (scaledRadius > 0.0f)
        {
            const Vector2 center = GetPosition();
            const float increment = Math::TwoPi / 32.0f;
            for (float r = 0.0f; r < Math::TwoPi; r += increment)
            {
                vertices.push_back(Vector2(center.X + scaledRadius * Math::Sin(r),
                                           center.Y + scaledRadius * Math::Cos(r)));
            }
        }
    }

    void SphereShape2D::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        SetRadius(reader.ReadFloat());
    }

    void SphereShape2D::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        radius = o->radius;
        radiusSquared = o->radiusSquared;
        scaledRadius = o->scaledRadius;
        scaledRadiusSquared = o->scaledRadiusSquared;
        revision = o->revision;
    }
}