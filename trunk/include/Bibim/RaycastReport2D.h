#pragma once
#ifndef __BIBIM_RAYCASTREPORT2D_H__
#define __BIBIM_RAYCASTREPORT2D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Vector2.h>

    namespace Bibim
    {
        struct RaycastReport2D
        {
            Shape2D* ImpactShape;
            Vector2  ImpactPoint;
            Vector2  ImpactNormal;
            float    ImpactDistance;

            inline RaycastReport2D();
            inline RaycastReport2D(Shape2D* shape, const Vector2& point, const Vector2& normal, float distance);
            inline RaycastReport2D(const RaycastReport2D& original);

            inline RaycastReport2D& operator = (const RaycastReport2D& original);
            
            inline bool operator == (const RaycastReport2D& right) const;
            inline bool operator != (const RaycastReport2D& right) const;
        };

        class IRaycastCallback2D
        {
            public:
                virtual ~IRaycastCallback2D() { }
                virtual bool OnHit(float distanceSquared) = 0;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

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

#endif