namespace Bibim
{
    RaycastReport2D::RaycastReport2D()
        : ImpactShape(0),
          ImpactPoint(Vector2::Zero),
          ImpactNormal(Vector2::Zero),
          ImpactDistance(0.0f)
    {
    }

    RaycastReport2D::RaycastReport2D(Shape2D* shape, const Vector2& point, const Vector2& normal, float distance)
        : ImpactShape(shape),
          ImpactPoint(point),
          ImpactNormal(normal),
          ImpactDistance(distance)
    {
    }

    RaycastReport2D::RaycastReport2D(const RaycastReport2D& original)
        : ImpactShape(original.ImpactShape),
          ImpactPoint(original.ImpactPoint),
          ImpactNormal(original.ImpactNormal),
          ImpactDistance(original.ImpactDistance)
    {
    }

    RaycastReport2D& RaycastReport2D::operator = (const RaycastReport2D& original)
    {
        ImpactShape = original.ImpactShape;
        ImpactPoint = original.ImpactPoint;
        ImpactNormal = original.ImpactNormal;
        ImpactDistance = original.ImpactDistance;
        return *this;
    }

    bool RaycastReport2D::operator == (const RaycastReport2D& right) const
    {
        return (ImpactShape == right.ImpactShape &&
                ImpactPoint == right.ImpactPoint &&
                ImpactNormal == right.ImpactNormal &&
                ImpactDistance == right.ImpactDistance);
    }

    bool RaycastReport2D::operator != (const RaycastReport2D& right) const
    {
        return !operator == (right);
    }
}