#include <Bibim/PCH.h>
#include <Bibim/SegmentShape2D.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Geom2D.h>
#include <Bibim/Math.h>
#include <Bibim/RaycastReport2D.h>

namespace Bibim
{
    BBImplementsComponent(SegmentShape2D);

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

    void SegmentShape2D::SetFrontLength(float value)
    {
        value = Math::Max(value, 0.0f);

        if (GetFrontLength() != value)
        {
            frontLength = value;
            revision = 0;
        }
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

    bool SegmentShape2D::Raycast(Vector2 origin, Vector2 direction, float length, RaycastReport2D& outReport, IRaycastCallback2D* callback)
    {
        float distance = 0.0f;
        if (Geom2D::RaycastSegment(origin, direction, length, GetStartPoint(), GetEndPoint(), distance))
        {
            if (callback == nullptr || callback->OnHit(distance * distance))
            {
                const Vector2 rotatedDirection = GetRotatedDirection();
                outReport.ImpactShape = this;
                outReport.ImpactPoint = origin + (direction * distance);
                outReport.ImpactNormal = Vector2(rotatedDirection.Y, rotatedDirection.X);
                outReport.ImpactDistance = distance;
                if (outReport.ImpactNormal.Dot(rotatedDirection) > 0.0f)
                    outReport.ImpactNormal = -outReport.ImpactNormal;

                return true;
            }
        }

        return false;
    }

    void SegmentShape2D::Build(Vertices& vertices)
    {
        if (GetScale() > 0.0f && GetLength() > 0.0f)
            vertices.Append(GetStartPoint(), GetEndPoint());
    }

    void SegmentShape2D::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        direction = reader.ReadVector2();
        frontLength = reader.ReadFloat();
        backLength = reader.ReadFloat();
        revision = 0;
    }

    void SegmentShape2D::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        direction = o->direction;
        frontLength = o->frontLength;
        backLength = o->backLength;
        startPoint = o->startPoint;
        endPoint = o->endPoint;
        rotatedDirection = o->rotatedDirection;
        revision = o->revision;
    }
}