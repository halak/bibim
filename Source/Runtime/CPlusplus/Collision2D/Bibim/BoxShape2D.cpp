#include <Bibim/PCH.h>
#include <Bibim/BoxShape2D.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Geom2D.h>
#include <Bibim/Math.h>
#include <Bibim/RaycastReport2D.h>

namespace Bibim
{
    BBImplementsComponent(BoxShape2D);

    BoxShape2D::BoxShape2D()
        : Shape2D(Shape2D::BoxType),
          orientation(Vector2::Zero),
          extension(Vector2::Zero),
          center(Vector2::Zero),
          rotatedOrientation(Vector2::Zero),
          rotatedUp(Vector2::Zero),
          scaledExtension(Vector2::Zero),
          p0(Vector2::Zero), p1(Vector2::Zero), p2(Vector2::Zero), p3(Vector2::Zero),
          revision(0)
    {
    }

    BoxShape2D::~BoxShape2D()
    {
    }

    void BoxShape2D::SetOrientation(Vector2 value)
    {
        if (value != Vector2::Zero)
            value.Normalize();

        if (GetOrientation() != value)
        {
            orientation = value;
            revision = 0;
        }
    }
   

    void BoxShape2D::SetExtension(Vector2 value)
    {
        if (GetExtension() != value)
        {
            extension = value;
            revision = 0;
        }
    }

    Vector2 BoxShape2D::GetCenter()
    {
        if (revision != GetSpatialRevision())
            UpdateParameters();

        return center;
    }

    Vector2 BoxShape2D::GetRotatedOrientation()
    {
        if (revision != GetSpatialRevision())
            UpdateParameters();

        return rotatedOrientation;
    }

    Vector2 BoxShape2D::GetRotatedUp()
    {
        if (revision != GetSpatialRevision())
            UpdateParameters();

        return rotatedUp;
    }

    Vector2 BoxShape2D::GetScaledExtension()
    {
        if (revision != GetSpatialRevision())
            UpdateParameters();

        return scaledExtension;
    }

    Vector2 BoxShape2D::GetP0()
    {
        if (revision != GetSpatialRevision())
            UpdateParameters();

        return p0;
    }

    Vector2 BoxShape2D::GetP1()
    {
        if (revision != GetSpatialRevision())
            UpdateParameters();

        return p1;
    }

    Vector2 BoxShape2D::GetP2()
    {
        if (revision != GetSpatialRevision())
            UpdateParameters();

        return p2;
    }

    Vector2 BoxShape2D::GetP3()
    {
        if (revision != GetSpatialRevision())
            UpdateParameters();

        return p3;
    }

    void BoxShape2D::UpdateParameters()
    {
        revision = GetSpatialRevision();
        center = GetPosition();
        rotatedOrientation = GetOrientation();
        rotatedOrientation.Rotate(GetRotation());
        rotatedUp = Vector2(+rotatedOrientation.Y, -rotatedOrientation.X);
        scaledExtension = GetExtension() * GetScale();
        p0 = center - (rotatedOrientation * scaledExtension.X) - (rotatedUp * scaledExtension.Y);
        p1 = center + (rotatedOrientation * scaledExtension.X) - (rotatedUp * scaledExtension.Y);
        p2 = center + (rotatedOrientation * scaledExtension.X) + (rotatedUp * scaledExtension.Y);
        p3 = center - (rotatedOrientation * scaledExtension.X) + (rotatedUp * scaledExtension.Y);
    }

    bool BoxShape2D::Raycast(Vector2 origin, Vector2 direction, float length, RaycastReport2D& outReport, IRaycastCallback2D* callback)
    {
        float distance = 0.0f;
        Vector2 normal = Vector2::Zero;
        if (Geom2D::RaycastBox(origin, direction, GetCenter(), GetRotatedOrientation(), GetScaledExtension(), distance, normal) && distance <= length)
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

    void BoxShape2D::AppendTo(std::list<Vector2>& vertices)
    {
        vertices.push_back(GetP0());
        vertices.push_back(GetP1());
        vertices.push_back(GetP2());
        vertices.push_back(GetP3());
    }

    void BoxShape2D::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        orientation = reader.ReadVector2();
        extension = reader.ReadVector2();
        revision = 0;
    }

    void BoxShape2D::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        orientation = o->orientation;
        extension = o->extension;
        center = o->center;
        rotatedOrientation = o->rotatedOrientation;
        rotatedUp = o->rotatedUp;
        scaledExtension = o->scaledExtension;
        p0 = o->p0;
        p1 = o->p1;
        p2 = o->p2;
        p3 = o->p3;
        revision = o->revision;
    }
}